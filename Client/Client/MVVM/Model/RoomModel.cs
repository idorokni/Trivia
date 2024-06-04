using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Client.MVVM.Model
{
    internal class RoomModel
    {
        private string _name;
        private List<string> _participants;
        private int _maxPlayers;
        private int _numOfQuestionsInGame;
        private int _timePerQuestion;

        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }

        public List<string> Participants
        {
            get { return _participants; }
            set { _participants = value; }
        }

        public RoomModel(List<string> participants, string name, int maxPlayers, int numOfQuestionsInGame, int timePerQuestion)
        {
            _participants = participants;
            _name = name;
            _maxPlayers = maxPlayers;
            _numOfQuestionsInGame = numOfQuestionsInGame;
            _timePerQuestion = timePerQuestion;
        }

        public int GetMaxPlayers() => _maxPlayers;
        public int GetNumOfQuestionsInGame() => _numOfQuestionsInGame;
        public int GetTimePerQuestion() => _timePerQuestion;
    }
}
