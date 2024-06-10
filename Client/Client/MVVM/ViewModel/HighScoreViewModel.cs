using Client.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.MVVM.ViewModel
{
    internal class HighScoreViewModel : ObservableObject
    {
        private Tuple<string, string> _firstScore;
        private Tuple<string, string> _secondScore;
        private Tuple<string, string> _thirdScore;
        private Tuple<string, string> _fourthScore;
        private Tuple<string, string> _fifthScore;

        public Tuple<string, string> FirstScore { get { return _firstScore; } }
        public Tuple<string, string> SecondScore { get { return _secondScore; } }
        public Tuple<string, string> ThirdScore { get { return _thirdScore; } }
        public Tuple<string, string> FourthScore { get { return _fourthScore; } }
        public Tuple<string, string> FifthScore { get { return _fifthScore; } }

    }
}
