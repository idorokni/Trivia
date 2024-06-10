using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.MVVM.Model
{
    internal class UserModel
    {
        private string _name;

        public string Name { get { return _name; }  set { _name = value; } }
    }
}
