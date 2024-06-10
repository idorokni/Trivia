using Client.MVVM.Model;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace Client
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public static Communicator Communicator { get; private set; }

        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            Communicator = new Communicator();
            Communicator.Connect();
        }
        /*protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            Communicator communicator = new Communicator();
            LoginRequest loginRequest = new LoginRequest("user134", "1234Aa!#");

            communicator.Connect();
            byte[] msg = communicator.SerializeLogIn(loginRequest);
            communicator.SendMessage(msg);

            RequestResult response = communicator.DeserializeMessage();
        }*/
    }
}

