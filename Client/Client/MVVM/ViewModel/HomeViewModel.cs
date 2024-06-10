using Client.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Proxies;
using System.Text;
using System.Threading.Tasks;

namespace Client.MVVM.ViewModel
{
    internal class HomeViewModel : ObservableObject
    {
        public RelayCommand CreateRoomViewCommand { get; set; }
        public RelayCommand JoinRoomViewCommand { get; set; }
        public RelayCommand UserStatsViewCommand { get; set; }

        public HomeViewModel()
        {
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
        }
    }
}
