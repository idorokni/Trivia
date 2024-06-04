using Client.Core;
using Client.MVVM.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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

        public JoinRoomViewModel()
        {
            List<string> check = new List<string>();
            check.Add("SDFSDF");
            check.Add("SDFSDF");
            
            //here should get rooms from server
            Rooms = new ObservableCollection<RoomModel>();
            JoinRoomCommand = new RelayCommand(o =>
            {
                MainViewModel.Instance.CurrentView = new InsideRoomViewModel(_room);
            });
            Rooms.Add(new RoomModel(check, "idodi", 1, 2, 3));
            Rooms.Add(new RoomModel(new List<string>(), "ido", 1, 2, 3));
        }
    }
}
