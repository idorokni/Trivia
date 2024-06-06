using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Windows.Markup;
using Newtonsoft.Json;

namespace Client.MVVM.Model
{
    internal class Communicator
    {
        private TcpClient client;
        private IPEndPoint serverEndPoint;
        private NetworkStream clientStream;

        public Communicator()
        {
            this.client = new TcpClient();
            this.serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8326);
        }

        public void Connect()
        {
            client.Connect(serverEndPoint);
            this.clientStream = client.GetStream();
        }

        public void SendMessage(byte[] buffer)
        {
            this.clientStream.Write(buffer, 0, buffer.Length);
            this.clientStream.Flush();
        }

        public byte[] SerializeLogIn(Request request)
        {
            // Convert message code to byte array
            byte codeByte = (byte)Client.MVVM.Model.RequestCode.LOGIN_REQUEST_CODE;
            byte[] codeBytes = new byte[] { codeByte };

            // Convert JSON data to byte array
            string jsonData = JsonConvert.SerializeObject(request);
            byte[] jsonDataBytes = Encoding.UTF8.GetBytes(jsonData);

            // Get length of data and convert it to byte array
            int dataLength = jsonData.Length;
            byte[] lengthBytes = BitConverter.GetBytes(dataLength);

            // Concatenate code, length, and JSON data byte arrays
            byte[] messageBytes = new byte[codeBytes.Length + lengthBytes.Length + jsonDataBytes.Length];
            Buffer.BlockCopy(codeBytes, 0, messageBytes, 0, codeBytes.Length);
            Buffer.BlockCopy(lengthBytes, 0, messageBytes, codeBytes.Length, lengthBytes.Length);
            Buffer.BlockCopy(jsonDataBytes, 0, messageBytes, codeBytes.Length + lengthBytes.Length, jsonDataBytes.Length);

            return messageBytes;
        }


        /*public string ReceiveMessage()
        {
            byte[] buffer = new byte[4096];
            int bytesRead = clientStream.Read(buffer, 0, buffer.Length);
            return Encoding.ASCII.GetString(buffer, 0, bytesRead);
        }*/

        public RequestResult DeserializeMessage()
        {
            byte[] codeBuffer = new byte[1];
            byte[] lengthBytes = new byte[4];

            clientStream.Read(codeBuffer, 0, codeBuffer.Length);

            // Extract message code (1 byte)
            byte codeByte = codeBuffer[0];
            RequestCode messageCode = (RequestCode)codeByte;

            clientStream.Read(lengthBytes, 0, lengthBytes.Length);
            // Extract length of data (4 bytes, little-endian)
            if (!BitConverter.IsLittleEndian)
            {
                Array.Reverse(lengthBytes); // Convert to little-endian if needed
            }
            int dataLength = BitConverter.ToInt32(lengthBytes, 0);

            // Extract data (dataLength bytes)
            byte[] dataBytes = new byte[dataLength];
            clientStream.Read(dataBytes, 0, dataBytes.Length);

            // Convert data to JSON string
            string jsonData = Encoding.UTF8.GetString(dataBytes);

            RequestResult resault = new RequestResult((int)messageCode, jsonData);
            return resault;
        }

        public void Close()
        {
            clientStream.Close();
            client.Close();
        }
    }
}
