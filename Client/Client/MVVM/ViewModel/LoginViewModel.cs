using Client.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Client.MVVM.View;
using Client.MVVM.ViewModel;
using Client.MVVM.Model;
using System.Windows;

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

        /*public LoginViewModel()
        {
            SubmitLoginCommand = new RelayCommand(o =>
            {
                Console.WriteLine(Username + " " + Password);
                MainViewModel.Instance.CurrentView = new HomeViewModel();
                MainWindow.mainWindow.ChangeVisibilityOfButton();
                MainViewModel.Instance.Username = _username;
            }, o => !string.IsNullOrEmpty(Username) && !string.IsNullOrEmpty(Password));

            SignupViewCommand = new RelayCommand(o =>
            {
                MainViewModel.Instance.CurrentView = new SignupViewModel();
            });
        }*/
        public LoginViewModel()
        {
            SubmitLoginCommand = new RelayCommand(o => ExecuteLogin(), o => CanExecuteLogin());
            SignupViewCommand = new RelayCommand(o => NavigateToSignup());
        }

        private bool CanExecuteLogin()
        {
            return !string.IsNullOrEmpty(Username) && !string.IsNullOrEmpty(Password);
        }

        private void ExecuteLogin()
        {
            try
            {
                LoginRequest loginRequest = new LoginRequest(Username, Password);

                byte[] msg = App.Communicator.Serialize(loginRequest, (int)Client.MVVM.Model.RequestCode.LOGIN_REQUEST_CODE);
                App.Communicator.SendMessage(msg);

                RequestResult response = App.Communicator.DeserializeMessage();
                // Handle the response here (e.g., check if login was successful)

                if (response.IsSuccess) 
                {
                    //MessageBox.Show("Login successful!");
                    MainViewModel.Instance.CurrentView = new HomeViewModel();
                    MainViewModel.Instance.ButtonVisibility = Visibility.Visible;
                    MainViewModel.Instance.Username = _username;
                }
                else
                {
                    MessageBox.Show("Login failed: " + response.Data);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred: " + ex.Message);
            }
        }

        private void NavigateToSignup()
        {
            MainViewModel.Instance.CurrentView = new SignupViewModel();
        }
    }
}
