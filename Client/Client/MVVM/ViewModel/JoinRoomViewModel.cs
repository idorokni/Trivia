using Client.Core;
using Client.MVVM.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Client.MVVM.ViewModel
{
    internal class JoinRoomViewModel
    {
        private ObservableCollection<RoomModel> _rooms;
        private RoomModel _room;

        public ObservableCollection<RoomModel> Rooms
        {
            get { return _rooms; }
            set { _rooms = value; }
        }

        public RoomModel Room
        {
            get { return _room; }
            set { _room = value; }
        }

        public RelayCommand JoinRoomCommand {  get; set; }

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

            //_rooms.Add(new RoomModel(new List<string>(), "shaharHamatok", 1, 2, 3, 0));
            try
            {
                //here should get rooms from server
                //Rooms = new ObservableCollection<RoomModel>();
                byte[] msg = new byte[] { (byte)Client.MVVM.Model.RequestCode.GET_ROOMS_REQUEST_CODE };
                App.Communicator.SendMessage(msg);

                RequestResult response = App.Communicator.DeserializeMessage();
                string[] rooms = response.Data.Split(';');

                foreach (string room in rooms)
                {
                    int userListStartIndex = room.IndexOf("userlist-");
                    int roomDataStartIndex = room.IndexOf("roomdata-");
                    List<string> participants = new List<string>();

                    if (userListStartIndex != -1 && roomDataStartIndex != -1 && userListStartIndex < roomDataStartIndex)
                    {
                        userListStartIndex += "userlist-".Length;
                        string participantsNamesSubstring = room.Substring(userListStartIndex, roomDataStartIndex - userListStartIndex);
                        string[] namesArray = participantsNamesSubstring.Split(',');
                        namesArray = namesArray.Take(namesArray.Length - 1).ToArray();
                        participants.AddRange(namesArray);

                        string roomDataSubstring = room.Substring(roomDataStartIndex + "roomdata-".Length);
                        string[] roomDataArray = roomDataSubstring.Split(',');

                        _rooms.Add(new RoomModel(participants, roomDataArray[0], int.Parse(roomDataArray[1]), int.Parse(roomDataArray[2]), int.Parse(roomDataArray[3]), uint.Parse(roomDataArray[4])));
                    }
                }

                /*
                JoinRoomCommand = new RelayCommand(o =>
                {
                    MainViewModel.Instance.CurrentView = new InsideRoomViewModel(_room);
                }, o => CanExecuteJoinRoom());
                */

                JoinRoomCommand = new RelayCommand(o =>
                {
                    JoinRoomRequest joinroomRequest = new JoinRoomRequest(_room.Id);

                    msg = App.Communicator.Serialize(joinroomRequest, (int)Client.MVVM.Model.RequestCode.JOIN_ROOM_REQUEST_CODE);
                    App.Communicator.SendMessage(msg);

                    response = App.Communicator.DeserializeMessage();
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
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred: " + ex.Message);
            }
        }
    }
}
