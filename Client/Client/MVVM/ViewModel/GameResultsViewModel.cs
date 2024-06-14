using Client.Core;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.MVVM.ViewModel
{
    internal class GameResultsViewModel : ObservableObject
    {
        private ObservableCollection<string> _userNames;
        private ObservableCollection<uint> _correctAnswers;
        private ObservableCollection<uint> _wrongAnswers;
        private ObservableCollection<uint> _averageAnswerTime;

        public ObservableCollection<string> Usernames {  get { return _userNames; } set { _userNames = value; OnPropertyChanged(); } }
        public ObservableCollection<uint> CorrectAnswers {  get { return _correctAnswers; } set { _correctAnswers = value; OnPropertyChanged(); } }
        public ObservableCollection<uint> WrongAnswers {  get { return _wrongAnswers; } set { _wrongAnswers = value; OnPropertyChanged(); } }
        public ObservableCollection<uint> AvgAnswerTime {  get { return _averageAnswerTime; } set { _averageAnswerTime = value; OnPropertyChanged(); } }

        public GameResultsViewModel()
        {
            Usernames = new ObservableCollection<string>();
            CorrectAnswers = new ObservableCollection<uint>();
            WrongAnswers = new ObservableCollection<uint>();
            AvgAnswerTime = new ObservableCollection<uint>();
            //should request here

        }
    }
}
