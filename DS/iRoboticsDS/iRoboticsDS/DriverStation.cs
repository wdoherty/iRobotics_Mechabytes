using System;
using System.Windows.Forms;
using Gamepadtest;
using System.IO.Ports;


namespace iRoboticsDS
{
    public partial class DriverStation : Form
    {
        GamepadState controller = new GamepadState(SlimDX.XInput.UserIndex.One);
        System.Windows.Threading.DispatcherTimer packetTransferTimer = new System.Windows.Threading.DispatcherTimer();
        System.Windows.Threading.DispatcherTimer findDevicesTimer = new System.Windows.Threading.DispatcherTimer();
        private byte[] controller_packet = new byte[8];
        private byte[] gui_packet = new byte[10];
        private byte[] data = new byte[10];
        int packet_time = 0;
        int i = 0;
        int period = 40;
        bool comms = false;
        int signal_integrity;
        int packet_index = 0;
        byte checkSumRX = 0;
        bool[] packet_state = new bool[25];
        private byte[] startByte = new byte[1];
        private byte[] checkSumTX = new byte[1];
        private byte[] endByte = new byte[1];

        byte mode = 0;

        public DriverStation()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            startByte[0] = 255;
            endByte[0] = 240;

            packetTransferTimer.Interval = new TimeSpan(0, 0, 0, 0, period);
            packetTransferTimer.Tick += new EventHandler(packetTransfer);

            findDevicesTimer.Interval = new TimeSpan(0, 0, 0, 0, period);
            findDevicesTimer.Tick += new EventHandler(findDevices);
            findDevicesTimer.Start();
        }

        private void findDevices(object sender, EventArgs e)
        {
            if (controllerComboBox.Text == "")
            {
                foreach (string portname in SerialPort.GetPortNames())
                {
                    controllerComboBox.Items.Add(portname);
                    controllerComboBox.Text = portname;
                }
            }

            if (controller != null && controller.Connected)
            {
                controller1_textBox.Text = "Connected";
                controller1_textBox.ForeColor = System.Drawing.Color.Green;
            }
            else
            {
                controller1_textBox.Text = "Disconnected";
                controller1_textBox.ForeColor = System.Drawing.Color.DarkRed;
            }
        }

        private void packetTransfer(object sender, EventArgs e)
        {
            packet_state[packet_time] = false;

            while (packet_index == 0 && serialPort.BytesToRead >= 26)
            {
                serialPort.ReadByte();
            }

            while (serialPort.BytesToRead > 0)
            {
                if (packet_index == 0)
                {
                    if (serialPort.ReadByte() == 255)
                    {
                        packet_index++;
                    }
                }else if (packet_index < 11)
                {
                    data[packet_index - 1] = Convert.ToByte(serialPort.ReadByte());
                    checkSumRX += data[packet_index - 1];
                    packet_index++;
                }else if (packet_index == 11)
                {
                    if(serialPort.ReadByte() == checkSumRX)
                    {
                        packet_index++;
                    }else
                    {
                        packet_index = 0;
                    }
                    checkSumRX = 0;
                }else if(packet_index == 12)
                {
                    if (serialPort.ReadByte() == 240)
                    {
                        for (i = 0; i < 8; i++)
                        {
                            gui_packet[i] = data[i];
                        }
                        packet_state[packet_time] = true;
                    }
                    packet_index = 0;
                }
            }
            updateArduinoReturnGUI();
            signal_integrity = 0;
            for (i=0; i<25; i++)
            {
                if (packet_state[packet_time])
                {
                    signal_integrity++;
                }
            }
            signal_integrity = signal_integrity * 100 / 25;

            packet_time = (packet_time + 1) % 25;

            updateGUIState();

            serialPort.DiscardOutBuffer();

            updateControllerState();

            serialPort.Write(startByte, 0, 1);
            serialPort.Write(controller_packet, 0, 8);
            serialPort.Write(checkSumTX, 0, 1);
            serialPort.Write(endByte, 0, 1);

        }
        
        private void updateControllerState()
        {
            if (controller != null && controller.Connected)
            {
                controller.Update();

                controller1_textBox.Text = "Connected";
                controller1_textBox.ForeColor = System.Drawing.Color.Green;

                i = 0;

                i = (Convert.ToInt32(controller.A)) |
                    (Convert.ToInt32(controller.B) << 1) |
                    (Convert.ToInt32(controller.X) << 2) |
                    (Convert.ToInt32(controller.Y) << 3) |
                    (Convert.ToInt32(controller.LeftShoulder) << 4) |
                    (Convert.ToInt32(controller.RightShoulder) << 5) |
                    (Convert.ToInt32(controller.Start) << 6);

                controller_packet[0] = Convert.ToByte(i);

                i = (Convert.ToInt32(controller.DPad.Up)) |
                    (Convert.ToInt32(controller.DPad.Down) << 1) |
                    (Convert.ToInt32(controller.DPad.Left) << 2) |
                    (Convert.ToInt32(controller.DPad.Right) << 3) |
                    (Convert.ToInt32(controller.LeftStick.Clicked) << 4) |
                    (Convert.ToInt32(controller.RightStick.Clicked) << 5) |
                    (Convert.ToInt32(controller.Back) << 6);

                controller_packet[1] = Convert.ToByte(i);
                
                controller_packet[2] = Convert.ToByte(controller.LeftStick.Position.X * 100 + 100);
                
                controller_packet[3] = Convert.ToByte(controller.LeftStick.Position.Y * 100 + 100);
                
               controller_packet[4] = Convert.ToByte(controller.RightStick.Position.X * 100 + 100);
                
                controller_packet[5] = Convert.ToByte(controller.RightStick.Position.Y * 100 + 100);
                
                controller_packet[6] = Convert.ToByte(controller.LeftTrigger * 100);
                
                controller_packet[7] = Convert.ToByte(controller.RightTrigger * 100);

                updateControllerGUI();

            }
            else
            {
                controller1_textBox.Text = "Disconnected";
                controller1_textBox.ForeColor = System.Drawing.Color.DarkRed;

                controller_packet[0] = Convert.ToByte(0);
                controller_packet[1] = Convert.ToByte(0);
                controller_packet[2] = Convert.ToByte(100);
                controller_packet[3] = Convert.ToByte(100);
                controller_packet[4] = Convert.ToByte(100);
                controller_packet[5] = Convert.ToByte(100);
                controller_packet[6] = Convert.ToByte(0);
                controller_packet[7] = Convert.ToByte(0);
            }

            checkSumTX[0] = 0;
            for (i = 0; i < 8; i++)
            {
                checkSumTX[0] += controller_packet[i];
            }

        }
        
        private void updateGUIState()
        {
            connection_textBox.Text = "     " + Convert.ToString(signal_integrity) + "%";
        }

        private void updateControllerGUI()
        {
            ControllerData1.Text = (controller_packet[0].ToString());
            ControllerData2.Text = (controller_packet[1].ToString());
            ControllerData3.Text = (controller_packet[2].ToString());
            ControllerData4.Text = (controller_packet[3].ToString());
            ControllerData5.Text = (controller_packet[4].ToString());
            ControllerData6.Text = (controller_packet[5].ToString());
            ControllerData7.Text = (controller_packet[6].ToString());
            ControllerData8.Text = (controller_packet[7].ToString());
        }

        private void updateArduinoReturnGUI()
        {
            //displays status of left drive train
            Pi0.Text = (gui_packet[0].ToString());
            DriveLeft_textbox.Text = (gui_packet[0].ToString());
            DriveLeft_textbox.ForeColor = System.Drawing.Color.White;

            //displays status of right drive train
            Pi1.Text = (gui_packet[1].ToString());
            DriveRight_textbox.Text = (gui_packet[1].ToString());
            DriveRight_textbox.ForeColor = System.Drawing.Color.White;

            if(gui_packet[2] == 0)
            {
                Mode_textbox.Text = "Simon Says";
            }
            else if (gui_packet[2] == 1)
            {
                Mode_textbox.Text = "Backpack";
            }
            else if (gui_packet[2] == 2)
            {
                Mode_textbox.Text = "Bowling Ball";
            }
            else
            {
                Mode_textbox.Text = "lol error";
            }

            //Mode_textbox.Text = (gui_packet[2].ToString());
            Mode_textbox.ForeColor = System.Drawing.Color.White;
            
            Pi2.Text = (gui_packet[2].ToString());

            if(Convert.ToInt32(gui_packet[3] & 1) == 1)
            {
                LL_textbox.Text = "1";
            }
            else
            {
                LL_textbox.Text = "0";
            }
            if (Convert.ToInt32(gui_packet[3] & 2) == 2)
            {
                LR_textbox.Text = "1";
            }
            else
            {
                LR_textbox.Text = "0";
            }
            if (Convert.ToInt32(gui_packet[3] & 4) == 4)
            {
                UL_textbox.Text = "1";
            }
            else
            {
                UL_textbox.Text = "0";
            }
            if (Convert.ToInt32(gui_packet[3] & 8) == 8)
            {
                UR_textbox.Text = "1";
            }
            else
            {
                UR_textbox.Text = "0";
            }
            if (Convert.ToInt32(gui_packet[3] & 16) == 16)
            {
                Backpack_intake_textbox.Text = "Outtake";
            }
            else if (Convert.ToInt32(gui_packet[3] & 32) == 32)
            {
                Backpack_intake_textbox.Text = "Intake";
            }
            else
            {
                Backpack_intake_textbox.Text = "Off";
            }
            if (Convert.ToInt32(gui_packet[3] & 64) == 64)
            {
                bowlingball_intake_textbx.Text = "Outtake";
            }
            else if (Convert.ToInt32(gui_packet[3] & 128) == 128)
            {
                bowlingball_intake_textbx.Text = "Intake";
            }
            else
            {
                bowlingball_intake_textbx.Text = "Off";
            }
            backpackSpeed_textbox.Text = (gui_packet[4].ToString());
            bowlingArmSpeed_textbox.Text = (gui_packet[5].ToString());

            
            Pi3.Text = (gui_packet[3].ToString());
            Pi4.Text = (gui_packet[4].ToString());
            Pi5.Text = (gui_packet[5].ToString());
            Pi6.Text = (gui_packet[6].ToString());
            Pi7.Text = (gui_packet[7].ToString());
        }

        private void open_button_Click(object sender, EventArgs e)
        {
            if (controllerComboBox.Text == "")
            {
                return;
            }

            if (!serialPort.IsOpen)
            {
                serialPort.PortName = controllerComboBox.Text;
                serialPort.Open();
            }
            else
            {
                return;
            }

            findDevicesTimer.Stop();
            System.Threading.Thread.Sleep(period);
            packetTransferTimer.Start();

        }

        private void close_button_Click(object sender, EventArgs e)
        {
            if (packetTransferTimer.IsEnabled)
            {
                packetTransferTimer.Stop();
            }
            System.Threading.Thread.Sleep(period);
            serialPort.Close();
            while (serialPort.IsOpen)
            {
                System.Threading.Thread.Sleep(10);
            }
            connection_textBox.Text = "   Closed";
            findDevicesTimer.Start();
        }

        private void refresh_button_Click(object sender, EventArgs e)
        {
            if (packetTransferTimer.IsEnabled)
            {
                packetTransferTimer.Stop();
            }
            System.Threading.Thread.Sleep(period);
            serialPort.Close();
            while (serialPort.IsOpen)
            {
                System.Threading.Thread.Sleep(10);
            }

            if (controllerComboBox.Text == "")
            {
                return;
            }

            if (!serialPort.IsOpen)
            {
                serialPort.PortName = controllerComboBox.Text;
                serialPort.Open();
            }
            else
            {
                return;
            }

            packetTransferTimer.Start();
        }

        private void iRoboticsCommandCenter_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (packetTransferTimer.IsEnabled)
            {
                packetTransferTimer.Stop();
            }
            System.Threading.Thread.Sleep(30);
            serialPort.Close();
            while (serialPort.IsOpen)
            {
                System.Threading.Thread.Sleep(30);
            }
        }
        private void label12_Click(object sender, EventArgs e)
        {

        }
        private void label17_Click(object sender, EventArgs e)
        {

        }
        private void label14_Click(object sender, EventArgs e)
        {

        }
        private void label4_Click(object sender, EventArgs e)
        {

        }
        private void label22_Click(object sender, EventArgs e)
        {

        }
        private void label23_Click(object sender, EventArgs e)
        {

        }

        private void label22_Click_1(object sender, EventArgs e)
        {

        }

        private void Mode_textbox_TextChanged(object sender, EventArgs e)
        {

        }

        private void label22_Click_2(object sender, EventArgs e)
        {

        }

        private void label22_Click_3(object sender, EventArgs e)
        {

        }
    }
}
