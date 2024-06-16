using Client.Core;
using Client.MVVM.Model;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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
        private int _currentQuestionNumber = 1;
        private ObservableCollection<string> _buttonNames;
        private string _question;
        private int _amountOfCorrectAnswers;
        private int _amountOfQuestions;

        public string Time { get { return _timeRepresentation; } set { _timeRepresentation = value; OnPropertyChanged(); } }
        public string Question { get { return _question; } set { _question = value; OnPropertyChanged(); } }
        public RelayCommand SwitchQuestion {  get; set; }
        public ObservableCollection<string> ButtonNames { get { return _buttonNames; } set { _buttonNames = value; OnPropertyChanged(); } }
        public int CurrentQuestionNumber { get { return _currentQuestionNumber; } set { _currentQuestionNumber = value; OnPropertyChanged(); } }
        public int AmountOfCorrectAnswers { get { return _amountOfCorrectAnswers; } set { _amountOfCorrectAnswers = value; OnPropertyChanged(); } }
        public int AmountOfQuestions { get { return _amountOfQuestions; } set { _amountOfQuestions = value; OnPropertyChanged(); } }

        public TriviaGameViewModel(int amountOfQuestions, int timePerQuestion)

        {
            SwitchQuestion = new RelayCommand(answerId =>
            {
                SubmitAnswerRequest submitAnswerRequest = new SubmitAnswerRequest(uint.Parse(((string)answerId)));
                byte[] msg = App.Communicator.Serialize(submitAnswerRequest, (int)Client.MVVM.Model.RequestCode.SUBMIT_ANSWER_REUEST_CODE);
                App.Communicator.SendMessage(msg);
                RequestResult response = App.Communicator.DeserializeMessage();
                if (response.IsSuccess && _currentQuestionNumber < amountOfQuestions)
                {
                    CurrentQuestionNumber++;
                    GetQuestionRequest getQuestionRequest = new GetQuestionRequest();
                    msg = App.Communicator.Serialize(submitAnswerRequest, (int)Client.MVVM.Model.RequestCode.SUBMIT_ANSWER_REUEST_CODE);
                    App.Communicator.SendMessage(msg);
                    response = App.Communicator.DeserializeMessage();
                    if (response.IsSuccess)
                    {
                        dynamic jsonObject = JsonConvert.DeserializeObject(response.Data);
                        
                        string[] answers = jsonObject.answers.split(',');
                        for(char i = 'a'; i <= 'd'; i++)
                        {
                            ButtonNames.Add(i + ". " + answers[i - 'a']);
                        }
                        //add question
                        _question = jsonObject.question;

                        _decrement = amountOfQuestions;
                    }
                    else
                    {
                        MessageBox.Show("Submit failed: " + response.Data);
                    }
                }
                else
                {
                    MessageBox.Show("Submit failed: " + response.Data);
                }

                if(_currentQuestionNumber == amountOfQuestions)
                {
                    MessageBox.Show("Login failed: " + response.Data);

                    MainViewModel.Instance.CurrentView = MainViewModel.Instance; //changed after creating final scores screen
                }


            });
            AmountOfQuestions = amountOfQuestions;
            _timePerQuestion = timePerQuestion;
            _decrement = _timePerQuestion;

            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(_timePerQuestion);
            timer.Tick += Timer_Tick;
            Time = _decrement.ToString();
            timer.Start();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            _decrement--;
            Time = _decrement.ToString();
            if(_decrement == 0)
            {
                SwitchQuestion.Execute("0");
            }
        }
    }
}
