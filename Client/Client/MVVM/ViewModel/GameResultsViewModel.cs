using Client.Core;
using Client.MVVM.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Threading;
using System.Windows;

namespace Client.MVVM.ViewModel
{
    internal class GameResultsViewModel : ObservableObject, IDisposable
    {
        private ObservableCollection<string> _userNames;
        private ObservableCollection<uint> _correctAnswers;
        private ObservableCollection<uint> _wrongAnswers;
        private ObservableCollection<uint> _averageAnswerTime;
        private BackgroundWorker background_worker = new BackgroundWorker();
        private bool _isDisposed = false;

        public ObservableCollection<string> Usernames { get { return _userNames; } set { _userNames = value; OnPropertyChanged(); } }
        public ObservableCollection<uint> CorrectAnswers { get { return _correctAnswers; } set { _correctAnswers = value; OnPropertyChanged(); } }
        public ObservableCollection<uint> WrongAnswers { get { return _wrongAnswers; } set { _wrongAnswers = value; OnPropertyChanged(); } }
        public ObservableCollection<uint> AvgAnswerTime { get { return _averageAnswerTime; } set { _averageAnswerTime = value; OnPropertyChanged(); } }

        public GameResultsViewModel()
        {
            Usernames = new ObservableCollection<string>();
            CorrectAnswers = new ObservableCollection<uint>();
            WrongAnswers = new ObservableCollection<uint>();
            AvgAnswerTime = new ObservableCollection<uint>();

            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;
            background_worker.DoWork += background_worker_DoWork;
            background_worker.RunWorkerCompleted += background_worker_RunWorkerCompleted;

            background_worker.RunWorkerAsync(3000);
        }

        private void background_worker_DoWork(object sender, DoWorkEventArgs e)
        {
            while (!background_worker.CancellationPending)
            {
                refreshGameResults();
                Thread.Sleep((int)e.Argument);
            }
        }

        private void background_worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Cancelled)
            {
                // Optionally handle cancellation
            }
            else
            {
                // Optionally handle completion
            }
        }

        private void refreshGameResults()
        {
            try
            {
                GetGameResultsRequest getGameResultsRequest = new GetGameResultsRequest();
                byte[] msg = App.Communicator.Serialize(getGameResultsRequest, (int)Client.MVVM.Model.RequestCode.GET_GAME_RESULT_REQUEST_CODE);
                App.Communicator.SendMessage(msg);

                RequestResult response = App.Communicator.DeserializeMessage();
                if (response.IsSuccess)
                {
                    string data = response.Data.Split(':')[1];
                    int statusPos = data.IndexOf(",\"status\"");
                    data = data.Substring(1, statusPos - 2);
                    string[] results = data.Split('-');
                    List<GameResultEntry> gameResults = new List<GameResultEntry>();

                    foreach (string result in results)
                    {
                        string[] resultParts = result.Split(',');
                        if (resultParts.Length >= 4)
                        {
                            string username = resultParts[0];
                            uint correctCount = uint.TryParse(resultParts[1], out uint correctValue) ? correctValue : 0;
                            uint wrongCount = uint.TryParse(resultParts[2], out uint wrongValue) ? wrongValue : 0;
                            uint avgTime = uint.TryParse(resultParts[3], out uint avgTimeValue) ? avgTimeValue : 0;

                            gameResults.Add(new GameResultEntry
                            {
                                Username = username,
                                CorrectAnswers = correctCount,
                                WrongAnswers = wrongCount,
                                AverageAnswerTime = avgTime
                            });
                        }
                    }

                    // Order by CorrectAnswers descending
                    gameResults = gameResults.OrderByDescending(r => r.CorrectAnswers).ToList();

                    // Clear and update ObservableCollection on UI thread
                    Application.Current.Dispatcher.Invoke(() =>
                    {
                        Usernames.Clear();
                        CorrectAnswers.Clear();
                        WrongAnswers.Clear();
                        AvgAnswerTime.Clear();

                        foreach (var result in gameResults)
                        {
                            Usernames.Add(result.Username);
                            CorrectAnswers.Add(result.CorrectAnswers);
                            WrongAnswers.Add(result.WrongAnswers);
                            AvgAnswerTime.Add(result.AverageAnswerTime);
                        }
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
    }
}
