using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Button;

namespace lab4_1
{
    public partial class Form1 : Form
    {
        private List<CCircle> circles = new List<CCircle>();
        public Form1()
        {
            InitializeComponent();
            this.DoubleBuffered = true;
            this.MouseDown += Form1_MouseDown;
            this.Paint += Form1_Paint;
            this.KeyDown += Form1_KeyDown;
            this.Resize += Form1_Resize;
            this.KeyPreview = true;
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                int countCircle = 0;
                foreach (var circle in circles)
                {
                    if (circle.Contains(e.Location))
                    {
                        countCircle += 1;
                        if (Control.ModifierKeys != Keys.Control)
                        {
                            if (countCircle == 1) 
                                foreach (var c in circles) c.isSelected = false;
                            circle.isSelected = true;
                        }
                        else
                        {
                            circle.isSelected = true;
                        }
                    }
                }

                if (countCircle == 0)
                {
                    foreach (var c in circles) c.isSelected = false;
                    CCircle circle = new CCircle(e.Location);
                    circles.Add(circle);
                }

                this.Invalidate();
            }
            
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            foreach (var circle in circles)
            {
                circle.Draw(e.Graphics);
            }
        }
        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                circles.RemoveAll(c => c.isSelected);
                this.Invalidate();
            }
        }


        private void Form1_Resize(object sender, EventArgs e) {
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            circles.Clear();
            this.Invalidate();
        }
    }

    public class CCircle
    {
        public const int radius = 30;
        public Point center;
        public bool isSelected;

        public CCircle(Point center)
        {
            this.center = center;
            this.isSelected = false;
        }

        public void Draw(Graphics g)
        {
            using (Brush brush = new SolidBrush(Color.Red))
            {
                g.FillEllipse(brush, center.X - radius, center.Y - radius, radius * 2, radius * 2);
            }
            if (isSelected)
            {
                using (Brush brush = new SolidBrush(Color.Blue)) { g.FillEllipse(brush, center.X - radius, center.Y - radius, radius * 2, radius * 2); }
                using (Brush brush = new SolidBrush(Color.Red)) { g.FillEllipse(brush, center.X - radius + 2, center.Y - radius + 2, radius * 2 - 4, radius * 2 - 4); }
            }
        }

        public bool Contains(Point point)
        {
            return (point.X - center.X) * (point.X - center.X) + (point.Y - center.Y) * (point.Y - center.Y) <= radius * radius;
        }
    }

}
