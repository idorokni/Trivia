using Client.Core;
using Client.MVVM.Model;
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
        private int _amountOfQuestions;
        private string _timeRepresentation;
        private int currentQuestionNumber = 1;
        private ObservableCollection<string> _buttonNames;

        public string Time { get { return _timeRepresentation; } set { _timeRepresentation = value; OnPropertyChanged(); } }
        public RelayCommand SwitchQuestion {  get; set; }
        public ObservableCollection<string> ButtonNames { get { return _buttonNames; } set { _buttonNames = value; OnPropertyChanged(); } }

        public TriviaGameViewModel(int amountOfQuestions, int timePerQuestion)
        {
            SwitchQuestion = new RelayCommand(answerId =>
            {
                SubmitAnswerRequest submitAnswerRequest = new SubmitAnswerRequest((uint)answerId);
                byte[] msg = App.Communicator.Serialize(submitAnswerRequest, (int)Client.MVVM.Model.RequestCode.SUBMIT_ANSWER_REUEST_CODE);
                App.Communicator.SendMessage(msg);
                RequestResult response = App.Communicator.DeserializeMessage();
                if (response.IsSuccess && currentQuestionNumber < amountOfQuestions)
                {
                    currentQuestionNumber++;
                    GetQuestionRequest getQuestionRequest = new GetQuestionRequest();
                    msg = App.Communicator.Serialize(submitAnswerRequest, (int)Client.MVVM.Model.RequestCode.SUBMIT_ANSWER_REUEST_CODE);
                    App.Communicator.SendMessage(msg);
                    response = App.Communicator.DeserializeMessage();
                    if (response.IsSuccess)
                    {

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

                if(currentQuestionNumber == amountOfQuestions)
                {
                    MessageBox.Show("Login failed: " + response.Data);

                    MainViewModel.Instance.CurrentView = MainViewModel.Instance; //changed after creating final scores screen
                }


            });

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
        }
    }
}
