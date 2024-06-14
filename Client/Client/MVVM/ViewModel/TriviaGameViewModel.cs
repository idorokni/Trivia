using Client.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Threading;

namespace Client.MVVM.ViewModel
{
    internal class TriviaGameViewModel : ObservableObject
    {
        private DispatcherTimer timer;
        private int _timePerQuestion;
        private int _decrement;
        private int _amountOfQuestions;
        private string _timeRepresentation;

        public string Time { get { return _timeRepresentation; } set { _timeRepresentation = value; OnPropertyChanged(); } }

        public TriviaGameViewModel(int amountOfQuestions, int timePerQuestion)
        {
            _amountOfQuestions = amountOfQuestions;
            _timePerQuestion = timePerQuestion;
            _decrement = _timePerQuestion;

            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(_timePerQuestion);
            timer.Tick += Timer_Tick;
            Time = _decrement.ToString();
            timer.Start();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            _decrement--;
            Time = _decrement.ToString();
        }
    }
}
