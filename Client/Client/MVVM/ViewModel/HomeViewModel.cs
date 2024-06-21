using Client.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Proxies;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Client.MVVM.ViewModel
{
    internal class HomeViewModel : ObservableObject
    {
        public RelayCommand CreateRoomViewCommand { get; set; }
        public RelayCommand JoinRoomViewCommand { get; set; }
        public RelayCommand UserStatsViewCommand { get; set; }
        public RelayCommand HighScoreViewCommand { get; set; }
        public RelayCommand _1v1ViewCommand { get; set; }

        public HomeViewModel()
        {
            MainViewModel.Instance.ButtonVisibility = Visibility.Visible;
            CreateRoomViewCommand = new RelayCommand(o =>
            {
                MainViewModel.Instance.CurrentView = new CreateRoomViewModel();
            });

            JoinRoomViewCommand = new RelayCommand(o =>
            {
                MainViewModel.Instance.CurrentView = new JoinRoomViewModel();
            });

            UserStatsViewCommand = new RelayCommand(o =>
            {
                MainViewModel.Instance.CurrentView = new UserStatsViewModel();
            });

            HighScoreViewCommand = new RelayCommand(o =>
            {
                MainViewModel.Instance.CurrentView = new HighScoreViewModel();
            });
            _1v1ViewCommand = new RelayCommand(o =>
            {
                MainViewModel.Instance.CurrentView = new WaitingViewModel();
            });

        }
    }
}
