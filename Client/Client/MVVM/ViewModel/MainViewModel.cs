using Client.Core;
using Client.MVVM.Model;
using Client.MVVM.View;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Client.MVVM.ViewModel
{
    internal class MainViewModel : ObservableObject
    {
        private object _currentView;
        private string _username;
        private Visibility _buttonVisibility = Visibility.Hidden;

        public static MainViewModel Instance { get; private set; }
        public RelayCommand BackToMenuCommand { get; set; }
        public RelayCommand SignupViewCommand { get; set; }
        public RelayCommand LogoutCommand { get; set; }
        public Visibility ButtonVisibility { get { return _buttonVisibility; } set { _buttonVisibility = value;  OnPropertyChanged(); } }

        public object CurrentView
        {
            get { return _currentView; }
            set { 
                _currentView = value;
                OnPropertyChanged();
            }
        }

        public string Username { get { return _username; } set { _username = value; OnPropertyChanged(); } }

        public MainViewModel()
        {
            Instance = this;
            CurrentView = new LoginViewModel();

            SignupViewCommand = new RelayCommand(o =>
            {
                CurrentView = new SignupViewModel();
            });

            BackToMenuCommand = new RelayCommand(o =>
            {
                CurrentView = new HomeViewModel();
            });

            LogoutCommand = new RelayCommand(o =>
            {
                LogoutRequest logoutRequest = new LogoutRequest();

                byte[] msg = App.Communicator.Serialize(logoutRequest, (int)Client.MVVM.Model.RequestCode.LOGOUT_REQUEST_CODE);
                App.Communicator.SendMessage(msg);

                RequestResult response = App.Communicator.DeserializeMessage();

                if (response.IsSuccess)
                {
                    MainViewModel.Instance.CurrentView = new LoginViewModel();
                    MainViewModel.Instance.ButtonVisibility = Visibility.Hidden;
                    MainViewModel.Instance.Username = null;
                }
                else
                {
                    MessageBox.Show("Login failed: " + response.Data);
                }
            });
        }
    }
}
