using Client.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Client.MVVM.View;
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

        public LoginViewModel()
        {
            SubmitLoginCommand = new RelayCommand(SubmitLogin, CanSubmitLogin);
        }

        private void SubmitLogin(object obj)
        {
            //here should be called a module function to connect with the server
            Console.WriteLine(Username + " " + Password);  
        }

        private bool CanSubmitLogin(object obj)
        {
            return !string.IsNullOrEmpty(Username) && !string.IsNullOrEmpty(Password);
        }
    }
}
