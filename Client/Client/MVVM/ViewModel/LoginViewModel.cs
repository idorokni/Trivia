using Client.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Client.MVVM.View;
using Client.MVVM.ViewModel;
namespace Client.MVVM.ViewModel
{
    internal class LoginViewModel : ObservableObject
    {
        private string _username;
        private string _password;

        public string Username
        {
            get { return _username; }
            set { _username = value; }
        }

        public string Password
        {
            get { return _password; }
            set { _password = value; }
        }

        public RelayCommand SubmitLoginCommand { get; set; }
        public RelayCommand SignupViewCommand {get; set; }

        public LoginViewModel()
        {
            SubmitLoginCommand = new RelayCommand(o =>
            {
                Console.WriteLine(Username + " " + Password);
                MainViewModel.Instance.CurrentView = new HomeViewModel();
            }, o => !string.IsNullOrEmpty(Username) && !string.IsNullOrEmpty(Password));

            SignupViewCommand = new RelayCommand(o =>
            {
                MainViewModel.Instance.CurrentView = new SignupViewModel();
            });
        }
    }
}
