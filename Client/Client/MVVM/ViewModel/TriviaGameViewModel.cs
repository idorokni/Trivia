using Client.Core;
using Client.MVVM.Model;
using Newtonsoft.Json;
using System;
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

        public string Time { get { return _timeRepresentation; } set { _timeRepresentation = value; OnPropertyChanged(); } }
        public string Question { get { return _question; } set { _question = value; OnPropertyChanged(); } }
        public RelayCommand SwitchQuestion { get; set; }
        public ObservableCollection<string> ButtonNames { get { return _buttonNames; } set { _buttonNames = value; OnPropertyChanged(); } }
        public int CurrentQuestionNumber { get { return _currentQuestionNumber; } set { _currentQuestionNumber = value; OnPropertyChanged(); } }
        public int AmountOfCorrectAnswers { get { return _amountOfCorrectAnswers; } set { _amountOfCorrectAnswers = value; OnPropertyChanged(); } }
        public int AmountOfQuestions { get { return _amountOfQuestions; } set { _amountOfQuestions = value; OnPropertyChanged(); } }

        public TriviaGameViewModel(int amountOfQuestions, int timePerQuestion)
        {
            AmountOfQuestions = amountOfQuestions;
            _timePerQuestion = timePerQuestion;
            _decrement = _timePerQuestion;

            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(1); // Timer ticks every second
            timer.Tick += Timer_Tick;
            Time = _decrement.ToString();
            timer.Start();

            ButtonNames = new ObservableCollection<string>();

            // Initial question retrieval
            GetQuestion();

            SwitchQuestion = new RelayCommand(answerId =>
            {
                SubmitAnswerRequest submitAnswerRequest = new SubmitAnswerRequest(uint.Parse((string)answerId));
                byte[] msg = App.Communicator.Serialize(submitAnswerRequest, (int)RequestCode.SUBMIT_ANSWER_REQUEST_CODE);
                App.Communicator.SendMessage(msg);
                RequestResult response = App.Communicator.DeserializeMessage();
                if (response.IsSuccess)
                {
                    if ((string)answerId == "1")
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
                    timer.Start();
                }
                else
                {
                    MessageBox.Show("Game over! Show final scores.");
                    MainViewModel.Instance.CurrentView = new GameResultsViewModel();
                }
            });
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            _decrement--;
            Time = _decrement.ToString();
            if (_decrement <= 0)
            {
                timer.Stop();
                SwitchQuestion.Execute("0");
            }
        }

        private void GetQuestion()
        {
            GetQuestionRequest getQuestionRequest = new GetQuestionRequest();
            byte[] msg = App.Communicator.Serialize(getQuestionRequest, (int)RequestCode.GET_QUESTION_REQUEST_CODE);
            App.Communicator.SendMessage(msg);
            GetQuestionResult getQuestionResult = App.Communicator.DeserializeGetQuestion();
            if (getQuestionResult.IsSuccess)
            {
                CurrentQuestionNumber++;
                ButtonNames.Clear();
                for (char i = 'a'; i <= 'd'; i++)
                {
                    ButtonNames.Add(i + ". " + getQuestionResult.answers[i - 'a']);
                }
                Question = getQuestionResult.question;
            }
        }
    }
}
