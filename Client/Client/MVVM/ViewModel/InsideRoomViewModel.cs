using Client.Core;
using Client.MVVM.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.MVVM.ViewModel
{
    internal class InsideRoomViewModel : ObservableObject
    {
        private RoomModel _room;

        public string Name { get; set; }
        public string MaxNumOfPlayers { get; set; }
        public InsideRoomViewModel(RoomModel roomModel)
        {
            _room = roomModel;
            Name = roomModel.Name;
            MaxNumOfPlayers = roomModel.
        }
    }
}
