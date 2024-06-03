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

        public ObservableCollection<RoomModel> Rooms
        {
            get { return _rooms; }
            set { _rooms = value; }
        }

        public JoinRoomViewModel()
        {
            //here should get rooms from server
            Rooms = new ObservableCollection<RoomModel>();
            Rooms.Add(new RoomModel(new List<string>(), "idodi"));
            Rooms.Add(new RoomModel(new List<string>(), "ido"));
        }
    }
}
