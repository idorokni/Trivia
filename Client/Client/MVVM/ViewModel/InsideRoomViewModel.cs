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

namespace Client.MVVM.ViewModel
{
    internal class InsideRoomViewModel : ObservableObject
    {
        private RoomModel _room;
        private BackgroundWorker background_worker = new BackgroundWorker();

        public RoomModel Room { get { return _room; } set { _room = value; } }
        public InsideRoomViewModel(RoomModel roomModel)
        {
            _room = roomModel;
            _room.Participants.Add(MainViewModel.Instance.Username);


            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;
            background_worker.DoWork += background_worker_DoWork;
            //background_worker.ProgressChanged += background_worker_ProgressChanged;
            background_worker.RunWorkerCompleted += background_worker_RunWorkerCompleted;

            background_worker.RunWorkerAsync(roomModel.Id);
        }

        private void background_worker_DoWork(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                if (background_worker.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }
                refreshScreen((uint)e.Argument);
                Thread.Sleep(3000);
            }
        }

        private void background_worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Cancelled)
            {
                MessageBox.Show("BackgroundWorker canceled");
            }
            else
            {
                MessageBox.Show("BackgroundWorker ended successfully");
            }
        }

        public void refreshScreen(uint roomId)
        {
            try
            {
                //here should get rooms from server
                GetRoomStateRequest getPlayersInRoomRequest = new GetRoomStateRequest();
                byte[] msg = App.Communicator.Serialize(getPlayersInRoomRequest, (int)Client.MVVM.Model.RequestCode.GET_ROOM_STATE_REQUEST_CODE);
                App.Communicator.SendMessage(msg);

                RequestResult response = App.Communicator.DeserializeMessage();
                string participantsPart = response.Data.Split(':')[3];
                int endIndex = participantsPart.IndexOf("\",\"questionCount\"");
                string[] participantsArray = response.Data.Split(':')[3].Substring(1, response.Data.Split(':')[3].IndexOf(",\",\"questionCount\"")).Split(',');
                participantsArray = participantsArray.Take(participantsArray.Length - 1).ToArray();
                Application.Current.Dispatcher.Invoke(() =>
                {
                    _room.Participants.Clear();
                    foreach (string participant in participantsArray)
                    {
                        if (!string.IsNullOrEmpty(participant))
                        {
                            _room.Participants.Add(participant);
                        }
                    }
                });
            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred: " + ex.Message);
            }
        }
    }
}
