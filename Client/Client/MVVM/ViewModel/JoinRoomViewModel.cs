using Client.Core;
using Client.MVVM.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Shapes;

namespace Client.MVVM.ViewModel
{
    internal class JoinRoomViewModel
    {
        private ObservableCollection<RoomModel> _rooms;
        private RoomModel _room;
        private BackgroundWorker background_worker = new BackgroundWorker();
        private uint _selectedRoomId;


        public ObservableCollection<RoomModel> Rooms
        {
            get { return _rooms; }
            set { _rooms = value; }
        }

        public RoomModel Room
        {
            get { return _room; }
            set
            {
                _room = value;
                // Update the selected room ID when the Room property changes
                if (_room != null)
                {
                    _selectedRoomId = _room.Id;
                }
            }
        }

        public RelayCommand JoinRoomCommand { get; set; }

        /*public JoinRoomViewModel()
        {
            _rooms = new ObservableCollection<RoomModel>();
            JoinRoomCommand = new RelayCommand(o => ExecuteJoinRoom(), o => CanExecuteJoinRoom());
        }*/

        private bool CanExecuteJoinRoom()
        {
            return _rooms.Count > 0 && _room != null;
        }

        public JoinRoomViewModel()
        {
            _rooms = new ObservableCollection<RoomModel>();
            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;

            background_worker.DoWork += background_worker_DoWork;
            //background_worker.ProgressChanged += background_worker_ProgressChanged;
            background_worker.RunWorkerCompleted += background_worker_RunWorkerCompleted;

            background_worker.RunWorkerAsync(3000);



            JoinRoomCommand = new RelayCommand(o =>
            {
                JoinRoomRequest joinroomRequest = new JoinRoomRequest(_room.Id);

                byte[] msg = App.Communicator.Serialize(joinroomRequest, (int)Client.MVVM.Model.RequestCode.JOIN_ROOM_REQUEST_CODE);
                App.Communicator.SendMessage(msg);

                RequestResult response = App.Communicator.DeserializeMessage();
                // Handle the response here (e.g., check if login was successful)

                if (response.IsSuccess)
                {
                    MainViewModel.Instance.CurrentView = new InsideRoomViewModel(_room);
                }
                else
                {
                    MessageBox.Show("Joinroom failed: " + response.Data);
                }
            }, o => CanExecuteJoinRoom());
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
                //Parameters parameter = refreshScreen();
                refreshScreen();
                //background_worker.ReportProgress((100 * i) / (int)e.Argument + 1, parameter);
                Thread.Sleep((int)e.Argument);
            }
        }

        /*private void background_worker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            Parameters parameter = e.UserState as Parameters;
            _rooms.Add(new RoomModel(participants, roomDataArray[0], int.Parse(roomDataArray[1]), int.Parse(roomDataArray[2]), int.Parse(roomDataArray[3]), uint.Parse(roomDataArray[4])));

            //txtInterationCounter.Text = e.ProgressPercentage.ToString() + " %";
        }*/
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

        public void refreshScreen()
        {
            try
            {
                //here should get rooms from server
                //_rooms = new ObservableCollection<RoomModel>();
                byte[] msg = new byte[] { (byte)Client.MVVM.Model.RequestCode.GET_ROOMS_REQUEST_CODE };
                App.Communicator.SendMessage(msg);

                RequestResult response = App.Communicator.DeserializeMessage();
                string[] rooms = response.Data.Split(';');
                Application.Current.Dispatcher.Invoke(() =>
                {
                    uint previouslySelectedRoomId = _selectedRoomId;
                    _rooms.Clear();

                    foreach (string room in rooms)
                    {
                        int userListStartIndex = room.IndexOf("userlist-");
                        int roomDataStartIndex = room.IndexOf("roomdata-");
                        ObservableCollection<string> participants = new ObservableCollection<string>();

                        if (userListStartIndex != -1 && roomDataStartIndex != -1 && userListStartIndex < roomDataStartIndex)
                        {
                            userListStartIndex += "userlist-".Length;
                            string participantsNamesSubstring = room.Substring(userListStartIndex, roomDataStartIndex - userListStartIndex);
                            string[] namesArray = participantsNamesSubstring.Split(',');
                            namesArray = namesArray.Take(namesArray.Length - 1).ToArray();
                            foreach(string name in namesArray)
                            {
                                participants.Add(name);
                            }

                            string roomDataSubstring = room.Substring(roomDataStartIndex + "roomdata-".Length);
                            string[] roomDataArray = roomDataSubstring.Split(',');

                            RoomModel newRoom = new RoomModel(participants, roomDataArray[0], int.Parse(roomDataArray[1]), int.Parse(roomDataArray[2]), int.Parse(roomDataArray[3]), uint.Parse(roomDataArray[4]));
                            _rooms.Add(newRoom);
                            if (newRoom.Id == previouslySelectedRoomId)
                            {
                                Room = newRoom;
                            }
                        }
                    }
                });
                /*
                JoinRoomCommand = new RelayCommand(o =>
                {
                    MainViewModel.Instance.CurrentView = new InsideRoomViewModel(_room);
                }, o => CanExecuteJoinRoom());
                */


            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred: " + ex.Message);
            }
        }

    }
}
