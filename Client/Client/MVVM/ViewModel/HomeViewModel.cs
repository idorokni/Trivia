using Client.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.MVVM.ViewModel
{
    internal class HomeViewModel : ObservableObject
    {
        public RelayCommand CreateRoomViewCommand { get; set; }

        public HomeViewModel()
        {
            CreateRoomViewCommand = new RelayCommand(o =>
            {
                MainViewModel.Instance.CurrentView = new CreateRoomViewModel();
            });
        }
    }
}
