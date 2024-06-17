using Client.Core;
using Client.MVVM.Model;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Threading;

namespace Client.MVVM.ViewModel
{
    internal class TriviaGameViewModel : ObservableObject
    {
        private DispatcherTimer timer;
        private int _timePerQuestion;
        private int _decrement;
        private string _timeRepresentation;
        private int _currentQuestionNumber;
        private ObservableCollection<string> _buttonNames;
        private string _question;
        private int _amountOfCorrectAnswers;
        private int _amountOfQuestions;
        private string _correctAnswerIndex;

        public string Time { get { return _timeRepresentation; } set { _timeRepresentation = value; OnPropertyChanged(); } }
        public string Question { get { return _question; } set { _question = value; OnPropertyChanged(); } }
        public RelayCommand SwitchQuestion { get; set; }
        public ObservableCollection<string> ButtonNames { get { return _buttonNames; } set { _buttonNames = value; OnPropertyChanged(); } }
        public int CurrentQuestionNumber { get { return _currentQuestionNumber; } set { _currentQuestionNumber = value; OnPropertyChanged(); } }
        public int AmountOfCorrectAnswers { get { return _amountOfCorrectAnswers; } set { _amountOfCorrectAnswers = value; OnPropertyChanged(); } }
        public int AmountOfQuestions { get { return _amountOfQuestions; } set { _amountOfQuestions = value; OnPropertyChanged(); } }

        public string CorrectAnswerIndex { get { return _correctAnswerIndex; } set { _correctAnswerIndex = value; OnPropertyChanged(); } }

        public TriviaGameViewModel(int amountOfQuestions, int timePerQuestion)
        {
            AmountOfQuestions = amountOfQuestions;
            _timePerQuestion = timePerQuestion;
            _decrement = _timePerQuestion;

            // Initialize and start the timer on the UI thread
            Application.Current.Dispatcher.Invoke(() =>
            {
                timer = new DispatcherTimer();
                timer.Interval = TimeSpan.FromSeconds(1); // Timer ticks every second
                timer.Tick += Timer_Tick;
                Time = _decrement.ToString();
                timer.Start();
            });

            ButtonNames = new ObservableCollection<string>();

            // Initial question retrieval
            GetQuestion();

            SwitchQuestion = new RelayCommand(answerId =>
            {
                SubmitAnswerRequest submitAnswerRequest;
                if ((string)answerId == _correctAnswerIndex)
                {
                    submitAnswerRequest = new SubmitAnswerRequest(uint.Parse("1"), (uint)(_timePerQuestion - _decrement));
                }
                else
                {
                    submitAnswerRequest = new SubmitAnswerRequest(uint.Parse("2"), (uint)(_timePerQuestion - _decrement));
                }
                byte[] msg = App.Communicator.Serialize(submitAnswerRequest, (int)RequestCode.SUBMIT_ANSWER_REQUEST_CODE);
                App.Communicator.SendMessage(msg);
                RequestResult response = App.Communicator.DeserializeMessage();
                if (response.IsSuccess)
                {
                    if ((string)answerId == _correctAnswerIndex)
                    {
                        AmountOfCorrectAnswers++;
                    }
                }
                else
                {
                    MessageBox.Show("Submit failed");
                }

                if (_currentQuestionNumber < AmountOfQuestions)
                {
                    GetQuestion(); // Move to the next question
                    // Restart the timer
                    _decrement = _timePerQuestion; // Reset decrement counter
                    Time = _decrement.ToString();
                    Application.Current.Dispatcher.Invoke(() => timer.Start());
                }
                else
                {
                    //MessageBox.Show("Game over! Show final scores.");
                    MainViewModel.Instance.CurrentView = new GameResultsViewModel();
                }
            });
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            _decrement--;

            // Update Time property on the UI thread
            Application.Current.Dispatcher.Invoke(() =>
            {
                Time = _decrement.ToString();
            });

            if (_decrement <= 0)
            {
                timer.Stop();
                // Execute on the UI thread
                Application.Current.Dispatcher.Invoke(() =>
                {
                    SwitchQuestion.Execute("0");
                });
            }
        }

        private void GetQuestion()
        {
            List<int> list = new List<int> { 0, 1, 2, 3 };

            GetQuestionRequest getQuestionRequest = new GetQuestionRequest();
            byte[] msg = App.Communicator.Serialize(getQuestionRequest, (int)RequestCode.GET_QUESTION_REQUEST_CODE);
            App.Communicator.SendMessage(msg);
            GetQuestionResult getQuestionResult = App.Communicator.DeserializeGetQuestion();
            if (getQuestionResult.IsSuccess)
            {
                CurrentQuestionNumber++;
                ButtonNames.Clear();
                for (int i = 0; i <= 3; i++)
                {
                    Shuffle(list);
                    int lastItem = list[list.Count - 1]; // Get the last item
                    list.RemoveAt(list.Count - 1); // Remove the last item
                    ButtonNames.Add(i + ". " + getQuestionResult.answers[lastItem].Split('-')[1]);
                    if (getQuestionResult.answers[lastItem].Contains("1-"))
                    {
                        CorrectAnswerIndex = (i + 1).ToString();
                    }

                }
                Question = getQuestionResult.question;
            }
        }

        private static void Shuffle(List<int> list)
        {
            Random rng = new Random();
            int n = list.Count;
            while (n > 1)
            {
                n--;
                int k = rng.Next(n + 1);
                int value = list[k];
                list[k] = list[n];
                list[n] = value;
            }
        }
    }
}
