using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.MVVM.Model
{
    
    struct ScoreModel
    {
        private string _username;
        private string _score;

        public string Username {  get { return _username; } set { _username = value; } }
        public string Score { get { return _score; } set { _score = value; } }

        public ScoreModel(string username, string score)
        {
            _username = username;
            _score = score;
        }
    }
}
