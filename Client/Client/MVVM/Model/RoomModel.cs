using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Client.MVVM.Model
{
    internal class RoomModel
    {
        private string _name;
        private ObservableCollection<string> _participants;
        private int _maxPlayers;
        private int _numOfQuestionsInGame;
        private int _timePerQuestion;
        private uint _id;

        public string Name {get { return _name; } set { _name = value; } }
        public ObservableCollection<string> Participants { get { return _participants; } set { _participants = value; } }
        public uint Id { get { return _id; } set { _id = value; } }
        public int MaxPlayers { get { return _maxPlayers; } set { _maxPlayers = value; } }
        public int NumOfQuestionsInGame { get { return _numOfQuestionsInGame; } set { _numOfQuestionsInGame = value; } }
        public int TimePerQuestion { get { return _timePerQuestion; } set { _timePerQuestion = value; } }

        public RoomModel(ObservableCollection<string> participants, string name, int maxPlayers, int numOfQuestionsInGame, int timePerQuestion, uint id)
        {
            _participants = participants;
            _name = name;
            _maxPlayers = maxPlayers;
            _numOfQuestionsInGame = numOfQuestionsInGame;
            _timePerQuestion = timePerQuestion;
            _id = id;
        }
    }
}
