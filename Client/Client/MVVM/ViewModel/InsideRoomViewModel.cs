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
        public int MaxNumOfPlayers { get; set; }
        public int AmountOfQuestions { get; set; }
        public int TimePerQuestion { get; set; }
        public List<string> Participants {  get; set; }
        public InsideRoomViewModel(RoomModel roomModel)
        {
            Name = roomModel.Name;
            MaxNumOfPlayers = roomModel.GetMaxPlayers();
            AmountOfQuestions = roomModel.GetNumOfQuestionsInGame();
            TimePerQuestion = roomModel.GetTimePerQuestion();
            Participants = roomModel.Participants;
        }
    }
}
