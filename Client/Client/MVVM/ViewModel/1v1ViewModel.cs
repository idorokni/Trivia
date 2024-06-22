using Client.Core;
using Client.MVVM.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;

namespace Client.MVVM.ViewModel
{
    internal class _1v1ViewModel : ObservableObject
    {
        private DispatcherTimer timer;
        private int _decrement;
        private string _timeRepresentation;
        private ObservableCollection<string> _buttonNames;
        private string _question;
        private string _correctAnswerIndex;
        private uint _health;
        private BackgroundWorker background_worker = new BackgroundWorker();
        private bool _isDisposed = false;

        public string Time { get { return _timeRepresentation; } set { _timeRepresentation = value; OnPropertyChanged(); } }
        public string Question { get { return _question; } set { _question = value; OnPropertyChanged(); } }
        public RelayCommand SwitchQuestion { get; set; }
        public RelayCommand LeaveGame { get; set; }
        public ObservableCollection<string> ButtonNames { get { return _buttonNames; } set { _buttonNames = value; OnPropertyChanged(); } }
        public string CorrectAnswerIndex { get { return _correctAnswerIndex; } set { _correctAnswerIndex = value; OnPropertyChanged(); } }
        public uint Health { get { return _health; } set { _health = value; OnPropertyChanged(); } }



        public _1v1ViewModel()
        {
            _decrement = 1;
            _health = 140;

            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;

            background_worker.DoWork += background_worker_DoWork;
            background_worker.RunWorkerCompleted += background_worker_RunWorkerCompleted;

            Application.Current.Dispatcher.Invoke(() =>
            {
                timer = new DispatcherTimer();
                timer.Interval = TimeSpan.FromSeconds(1); // Timer ticks every second
                timer.Tick += Timer_Tick;
                Time = _decrement.ToString();
                timer.Start();
            });

            ButtonNames = new ObservableCollection<string>();

            LeaveGame = new RelayCommand(o =>
            {
                LeaveGameRequest leaveGameRequest = new LeaveGameRequest();

                byte[] msg = App.Communicator.Serialize(leaveGameRequest, (int)Client.MVVM.Model.RequestCode.LEAVE_GAME_REQUEST_CODE);
                App.Communicator.SendMessage(msg);

                RequestResult response = App.Communicator.DeserializeMessage();
                // Handle the response here (e.g., check if login was successful)

                if (response.IsSuccess)
                {
                    timer.Stop();
                    MainViewModel.Instance.CurrentView = new HomeViewModel();
                }
                else
                {
                    MessageBox.Show("Leave room failed: " + response.Data);
                }
            });

            // Initial question retrieval
            GetQuestion();

            SwitchQuestion = new RelayCommand(answerId =>
            {
                SubmitAnswerRequest submitAnswerRequest;
                if ((string)answerId == _correctAnswerIndex)
                {
                    submitAnswerRequest = new SubmitAnswerRequest(uint.Parse("1"), (uint)(_decrement));
                }
                else
                {
                    submitAnswerRequest = new SubmitAnswerRequest(uint.Parse("2"), (uint)(_decrement));
                }
                byte[] msg = App.Communicator.Serialize(submitAnswerRequest, (int)RequestCode.SUBMIT_ANSWER_REQUEST_CODE);
                App.Communicator.SendMessage(msg);
                RequestResult response = App.Communicator.DeserializeMessage();
                if (!response.IsSuccess)
                {
                    MessageBox.Show("Submit failed");
                }

                if (_health > 0)
                {
                    GetQuestion(); // Move to the next question
                    Application.Current.Dispatcher.Invoke(() => timer.Stop());
                    // Restart the timer
                    _decrement = 1; // Reset decrement counter
                    Time = _decrement.ToString();
                    Application.Current.Dispatcher.Invoke(() => timer.Start());
                }
            });

            background_worker.RunWorkerAsync(3000);
        }

        private void background_worker_DoWork(object sender, DoWorkEventArgs e)
        {
            while (!background_worker.CancellationPending)
            {
                refreshScreen();
                Thread.Sleep((int)e.Argument);
            }
        }

        private void background_worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Cancelled)
            {
                //MessageBox.Show("BackgroundWorker canceled");
            }
            else
            {
                //MessageBox.Show("BackgroundWorker ended successfully");
            }
        }

        public void refreshScreen()
        {
            try
            {
                // Here should get rooms from server
                byte[] msg = new byte[] { (byte)Client.MVVM.Model.RequestCode.GET_HEAD_ON_GAME_STATE_REQUEST_CODE };
                App.Communicator.SendMessage(msg);

                RequestResult response = App.Communicator.DeserializeMessage();
                int health = int.Parse(response.Data.Split(':')[1].Split(',')[0]);
                if (int.Parse(response.Data.Split(':')[2].Split(',')[0]) == 1)
                {
                    MainViewModel.Instance.CurrentView = new HeadOnGameResultsViewModel(true);
                    Application.Current.Dispatcher.Invoke(() => timer.Stop());
                    Dispose();
                }
                if (health <= 0)
                {
                    MainViewModel.Instance.CurrentView = new HeadOnGameResultsViewModel(false);
                    Application.Current.Dispatcher.Invoke(() => timer.Stop());
                    Dispose();
                }
                else
                {

                    Application.Current.Dispatcher.Invoke(() => {
                        Health = (uint)health;
                    });
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred: " + ex.Message);
            }
        }

        public void Dispose()
        {
            if (!_isDisposed)
            {
                background_worker.CancelAsync();
                background_worker.Dispose();
                _isDisposed = true;
            }
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            _decrement++;

            // Update Time property on the UI thread
            Application.Current.Dispatcher.Invoke(() =>
            {
                Time = _decrement.ToString();
            });
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
