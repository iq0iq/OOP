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

namespace lab4
{
    public partial class Form1 : Form
    {
        private List<Figure> figures = new List<Figure>();
        public Form1()
        {
            InitializeComponent();
            this.DoubleBuffered = true;
            this.KeyPreview = true;
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            foreach (var figure in figures)
                figure.Draw(e.Graphics);
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                int count = 0;
                foreach (var figure in figures)
                {
                    if (figure.Contains(e.Location))
                    {
                        count += 1;
                        if (Control.ModifierKeys != Keys.Control)
                        {
                            foreach (var f in figures) f.isSelected = false;
                            figure.isSelected = true;
                            break;
                        }
                        figure.isSelected = true;
                    }
                }
                if (count == 0)
                {
                    foreach (var f in figures) f.isSelected = false;
                }

                pictureBox1.Invalidate();
            }

        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.OemMinus:
                    if (e.Control)
                    {
                        foreach (var figure in figures)
                            if (figure.isSelected) figure.MakeSmaller();
                    }
                    break;
                case Keys.Oemplus:
                    if (e.Control)
                    {
                        foreach (var figure in figures)
                            if (figure.isSelected) figure.MakeBigger(pictureBox1.Width, pictureBox1.Height);
                    }
                    break;
                case Keys.Delete:
                    figures.RemoveAll(f => f.isSelected);
                    break;
                case Keys.W:
                    foreach (var figure in figures)
                        if (figure.isSelected) figure.Move(0, -2, pictureBox1.Width, pictureBox1.Height);
                    break;
                case Keys.S:
                    foreach (var figure in figures)
                        if (figure.isSelected) figure.Move(0, 2, pictureBox1.Width, pictureBox1.Height);
                    break;
                case Keys.A:
                    foreach (var figure in figures)
                        if (figure.isSelected) figure.Move(-2, 0, pictureBox1.Width, pictureBox1.Height);
                    break;
                case Keys.D:
                    foreach (var figure in figures)
                        if (figure.isSelected) figure.Move(2, 0, pictureBox1.Width, pictureBox1.Height);
                    break;
            }
            pictureBox1.Invalidate();
        }
        private void circle_Click(object sender, EventArgs e)
        {
            figures.Add(new Circle { });
            pictureBox1.Invalidate();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            colorDialog1.ShowDialog();
            foreach (var figure in figures)
                if (figure.isSelected) figure.ChangeColor(colorDialog1.Color);
            pictureBox1.Invalidate();
        }

        private void square_Click(object sender, EventArgs e)
        {
            figures.Add(new Square {});
            pictureBox1.Invalidate();
        }

        private void triangle_Click(object sender, EventArgs e)
        {
            figures.Add(new Triangle { });
            pictureBox1.Invalidate();
        }
    }


    abstract class Figure
    {
        public bool isSelected;
        public Color color;
        public abstract void Draw(Graphics g);
        public abstract bool Contains(Point p);
        public abstract bool CanMove(int x, int y, int borderX, int borderY);
        public abstract void Move(int x, int y, int borderX, int borderY);
        public abstract void MakeBigger(int borderX, int borderY);
        public abstract void MakeSmaller();
        public void ChangeColor(Color color) => this.color = color;
    }

    class Circle : Figure
    {
        private int radius;
        private Point center;
        public Circle() {
            center = new Point(100, 100);
            radius = 30;
            color = Color.Red;
            isSelected = false;
        }

        public override void Draw(Graphics g)
        {
            using (Brush brush = new SolidBrush(color))
            {
                g.FillEllipse(brush, center.X - radius, center.Y - radius, radius * 2, radius * 2);
            }
            if (isSelected)
            {
                g.FillEllipse(Brushes.Blue, center.X - radius, center.Y - radius, radius * 2, radius * 2);
                using (Brush brush = new SolidBrush(color)) { g.FillEllipse(brush, center.X - radius + 2, center.Y - radius + 2, radius * 2 - 4, radius * 2 - 4); }
            }
        }

        public override bool Contains(Point point)
        {
            return (point.X - center.X) * (point.X - center.X) + (point.Y - center.Y) * (point.Y - center.Y) <= radius * radius;
        }
        public override bool CanMove(int x, int y, int borderX, int borderY)
        {
            return center.Y + y - radius >= 0 && center.Y + y + radius <= borderY && center.X + x - radius >= 0 && center.X + x + radius <= borderX;
        }
        public override void Move(int x, int y, int borderX, int borderY)
        {
            if (CanMove(x, y, borderX, borderY))
            {
                center.Y += y;
                center.X += x;
            }  
        }
        public override void MakeBigger(int borderX, int borderY)
        {
            if (CanMove(1, 1, borderX, borderY) && CanMove(-1, -1, borderX, borderY))
                radius += 2;
        }
        public override void MakeSmaller()
        {
            if (radius >= 3) radius -= 2;
        }
    }

    class Square : Figure
    {
        private Point point;
        private int side;
        public Square()
        {
            point = new Point(100, 100);
            side = 60;
            color = Color.Red;
            isSelected = false;
        }

        public override void Draw(Graphics g)
        {
            using (Brush brush = new SolidBrush(color))
            {
                g.FillRectangle(brush, point.X, point.Y, side, side);
            }
            if (isSelected)
            {
                g.FillRectangle(Brushes.Blue, point.X, point.Y, side, side); 
                using (Brush brush = new SolidBrush(color)) { g.FillRectangle(brush, point.X + 2, point.Y + 2, side - 4, side - 4); }
            }
        }

        public override bool Contains(Point point)
        {
            return this.point.X <= point.X && this.point.Y <= point.Y && this.point.X + side >= point.X && this.point.Y + side >= point.Y;
        }
        public override bool CanMove(int x, int y, int borderX, int borderY)
        {
            return point.Y + y >= 0 && point.Y + y + side <= borderY && point.X + x >= 0 && point.X + x + side <= borderX;
        }
        public override void Move(int x, int y, int borderX, int borderY)
        {
            if (CanMove(x, y, borderX, borderY))
            {
                point.Y += y;
                point.X += x;
            }
        }
        public override void MakeBigger(int borderX, int borderY)
        {
            if (CanMove(-1, -1, borderX, borderY) && CanMove(1, 1, borderX, borderY))
            {
                side += 2;
                point.X -= 1;
                point.Y -= 1;
            }
        }
        public override void MakeSmaller()
        {
            if (side >= 3)
            {
                point.X += 1;
                point.Y += 1;
                side -= 2;
            }
        }
    }

    class Triangle : Figure
    {
        private Point[] points = new Point[3];
        public Triangle()
        {
            points[0] = new Point(100, 100);
            points[1] = new Point(180, 100);
            points[2] = new Point(140, 50);
            color = Color.Red;
            isSelected = false;
        }

        public override void Draw(Graphics g)
        {
            using (Brush brush = new SolidBrush(color))
            {
                g.FillPolygon(brush, points);
            }
            if (isSelected)
            {
                g.FillPolygon(Brushes.Blue, points);
                Point[] points2 = (Point[])points.Clone();
                points2[0].X += 4;
                points2[0].Y -= 2;
                points2[1].X -= 4;
                points2[1].Y -= 2;
                points2[2].Y += 3;
                using (Brush brush = new SolidBrush(color)) { g.FillPolygon(brush, points2); ; }
            }
        }

        public override bool Contains(Point point)
        {
            int k1 = (points[2].Y - points[0].Y) / (points[2].X - points[0].X);
            int b1 = points[2].Y - k1 * points[2].X;
            int k2 = (points[2].Y - points[1].Y) / (points[2].X - points[1].X);
            int b2 = points[2].Y - k2 * points[2].X;
            return point.Y >= k1 * point.X + b1 && point.Y >= k2 * point.X + b2 && point.Y <= points[0].Y;
        }
        public override bool CanMove(int x, int y, int borderX, int borderY)
        {
            return points[2].Y + y >= 0 && points[0].Y + y <= borderY && points[0].X + x >= 0 && points[1].X + x <= borderX;
        }
        public override void Move(int x, int y, int borderX, int borderY)
        {
            if (CanMove(x, y, borderX, borderY))
            {
                points[2].Y += y;
                points[1].Y += y;
                points[0].Y += y;
                points[2].X += x;
                points[1].X += x;
                points[0].X += x;
            }
        }
        public override void MakeBigger(int borderX, int borderY)
        {
            if (CanMove(-4, 2, borderX, borderY) && CanMove(4, -3, borderX, borderY))
            {
                points[0].X -= 4;
                points[0].Y += 2;
                points[1].X += 4;
                points[1].Y += 2;
                points[2].Y -= 3;
            }
        }
        public override void MakeSmaller()
        {
            if (points[1].X - points[0].X >= 10)
            {
                points[0].X += 4;
                points[0].Y -= 2;
                points[1].X -= 4;
                points[1].Y -= 2;
                points[2].Y += 3;
            }
        }
    }
}

