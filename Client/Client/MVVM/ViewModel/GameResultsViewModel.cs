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


    }
}
