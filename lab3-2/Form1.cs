using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;

namespace lab4_2
{
    public partial class Form1 : Form
    {
        Model model;
        public Form1()
        {
            InitializeComponent();
            model = new Model();
            model.observers += new System.EventHandler(UpdateFromModel);
        }

        private void UpdateFromModel(object sender, EventArgs e)
        {
            textBox1.Text = model.getValueA().ToString();
            textBox2.Text = model.getValueB().ToString();
            textBox3.Text = model.getValueC().ToString();
            numericUpDown1.Value = model.getValueA();
            numericUpDown2.Value = model.getValueB();
            numericUpDown3.Value = model.getValueC();
            trackBar1.Value = model.getValueA();
            trackBar2.Value = model.getValueB();
            trackBar3.Value = model.getValueC();
        }
        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            model.setValueA(Decimal.ToInt32(numericUpDown1.Value));
        }
        private void numericUpDown2_ValueChanged(object sender, EventArgs e)
        {
            model.setValueB(Decimal.ToInt32(numericUpDown2.Value));
        }
        private void numericUpDown3_ValueChanged(object sender, EventArgs e)
        {
            model.setValueC(Decimal.ToInt32(numericUpDown3.Value));
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            UpdateFromModel(sender, e);
        }

        private void trackBar1_ValueChanged(object sender, EventArgs e)
        {
            model.setValueA(trackBar1.Value);
        }

        private void trackBar2_ValueChanged(object sender, EventArgs e)
        {
            model.setValueB(trackBar2.Value);
        }

        private void trackBar3_ValueChanged(object sender, EventArgs e)
        {
            model.setValueC(trackBar3.Value);
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                if (int.TryParse(textBox1.Text, out int number))
                    model.setValueA(Int32.Parse(textBox1.Text));
                else textBox1.Text = model.getValueA().ToString();
            }
        }

        private void textBox2_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                if (int.TryParse(textBox2.Text, out int number))
                    model.setValueB(Int32.Parse(textBox2.Text));
                else textBox2.Text = model.getValueB().ToString();
            }
        }

        private void textBox3_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                if (int.TryParse(textBox3.Text, out int number))
                    model.setValueC(Int32.Parse(textBox3.Text));
                else textBox3.Text = model.getValueC().ToString();
            }
        }


        private void textBox1_Leave(object sender, EventArgs e)
        {
            if (int.TryParse(textBox1.Text, out int number))
                model.setValueA(Int32.Parse(textBox1.Text));
            else textBox1.Text = model.getValueA().ToString();
        }

        private void textBox2_Leave(object sender, EventArgs e)
        {
            if (int.TryParse(textBox2.Text, out int number))
                model.setValueB(Int32.Parse(textBox2.Text));
            else textBox2.Text = model.getValueB().ToString();
        }

        private void textBox3_Leave(object sender, EventArgs e)
        {
            if (int.TryParse(textBox3.Text, out int number))
                model.setValueC(Int32.Parse(textBox3.Text));
            else textBox3.Text = model.getValueC().ToString();
        }
    }

    public class Model
    {
        private int valueA;
        private int valueB;
        private int valueC;
        public System.EventHandler observers;
        public Model()
        {
            valueA = Properties.Settings.Default.valueA;
            valueB = Properties.Settings.Default.valueB;
            valueC = Properties.Settings.Default.valueC;
        }
        ~Model()
        {
            Properties.Settings.Default.valueA = valueA;
            Properties.Settings.Default.valueB = valueB;
            Properties.Settings.Default.valueC = valueC;
            Properties.Settings.Default.Save();
        }

        public void setValueA (int value)
        {
            if (value >= 0 && value <= 100)
            {
                valueA = value;
                if (value > valueB) valueB = value;
                if (valueC < value) valueC = value;
            }
            observers.Invoke(this, EventArgs.Empty);
        }
        public void setValueB(int value)
        {
            if (valueA <= value && value <= valueC) this.valueB = value;
            observers.Invoke(this, EventArgs.Empty);
        }
        public void setValueC(int value)
        {
            if (value >= 0 && value <= 100)
            {
                valueC = value;
                if (value < valueB) valueB = value;
                if (valueA > value) valueA = value;
            }
            observers.Invoke(this, EventArgs.Empty);
        }
        public int getValueA()
        {
            return valueA;
        }
        public int getValueB()
        {
            return valueB;
        }
        public int getValueC()
        {
            return valueC;
        }
    }
}
