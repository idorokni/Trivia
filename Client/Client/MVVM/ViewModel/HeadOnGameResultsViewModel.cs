using Client.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Client.MVVM.ViewModel
{
    internal class HeadOnGameResultsViewModel : ObservableObject
    {
        private Visibility _winnerVisibility = Visibility.Hidden;
        public Visibility WinnerVisibility { get { return _winnerVisibility; } set { _winnerVisibility = value; OnPropertyChanged(); } }
        private Visibility _loserVisibility = Visibility.Hidden;
        public Visibility LoserVisibility { get { return _loserVisibility; } set { _loserVisibility = value; OnPropertyChanged(); } }
        public HeadOnGameResultsViewModel(bool isWinner)
        {
            if (isWinner) WinnerVisibility = Visibility.Visible;
            else LoserVisibility = Visibility.Visible;
            MainViewModel.Instance.ButtonVisibility = Visibility.Visible;
        }
    }
}
