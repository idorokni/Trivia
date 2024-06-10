using Client.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.MVVM.ViewModel
{
    internal class UserStatsViewModel : ObservableObject
    {
        private string _name;
        private string _avgAnswerTime;
        private string _numOfCorrectAnswers;
        private string _numOfTotalAnswers;
        private string _numOfGamesPlayed;

        public string Name {  get { return _name; } set { _name = value; } }
        public string AvgAnswerTime { get { return _avgAnswerTime; } set { _avgAnswerTime = value; } }
        public string NumOfCorrectAnswers { get { return _numOfCorrectAnswers; } set { _numOfCorrectAnswers = value; } }
        public string NumOfTotalAnswers { get { return _numOfTotalAnswers; } set { _numOfTotalAnswers = value; } }
        public string NumOfGamesPlayed { get { return _numOfGamesPlayed; } set { _numOfGamesPlayed = value; } }

        public UserStatsViewModel()
        {
            _name = "SDFSF";
        }
    }
}
