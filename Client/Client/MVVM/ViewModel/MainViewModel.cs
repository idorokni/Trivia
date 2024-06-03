using Client.Core;
using Client.MVVM.View;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.MVVM.ViewModel
{
    internal class MainViewModel : ObservableObject
    {
        private object _currentView;

        public static MainViewModel Instance {  get; private set; }

        public LoginViewModel LoginVM { get; set; }
        public SignupViewModel SignupVM { get; set; }

        public RelayCommand SignupViewCommand {  get; set; }

        public object CurrentView
        {
            get { return _currentView; }
            set { 
                _currentView = value;
                OnPropertyChanged();
            }
        }

        public MainViewModel()
        {
            Instance = this;
            LoginVM = new LoginViewModel();
            SignupVM = new SignupViewModel();
            CurrentView = LoginVM;

            SignupViewCommand = new RelayCommand(o =>
            {
                CurrentView = SignupVM;
            });
        }
    }
}
