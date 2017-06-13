namespace OV7725调车上位机
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.tabControl3 = new System.Windows.Forms.TabControl();
            this.tabPage7 = new System.Windows.Forms.TabPage();
            this.button2 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.tabControl4 = new System.Windows.Forms.TabControl();
            this.tabPage9 = new System.Windows.Forms.TabPage();
            this.button5 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button9 = new System.Windows.Forms.Button();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.tabControl2 = new System.Windows.Forms.TabControl();
            this.tabPage6 = new System.Windows.Forms.TabPage();
            this.button13 = new System.Windows.Forms.Button();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.button8 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.groupBox1.SuspendLayout();
            this.tabControl3.SuspendLayout();
            this.tabPage7.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.tabControl4.SuspendLayout();
            this.tabPage9.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.tabControl2.SuspendLayout();
            this.tabPage6.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.tabControl3);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(173, 279);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "通讯设置";
            // 
            // tabControl3
            // 
            this.tabControl3.Controls.Add(this.tabPage7);
            this.tabControl3.Location = new System.Drawing.Point(7, 48);
            this.tabControl3.Name = "tabControl3";
            this.tabControl3.SelectedIndex = 0;
            this.tabControl3.Size = new System.Drawing.Size(160, 217);
            this.tabControl3.TabIndex = 0;
            // 
            // tabPage7
            // 
            this.tabPage7.BackColor = System.Drawing.Color.LightGreen;
            this.tabPage7.Controls.Add(this.button2);
            this.tabPage7.Controls.Add(this.label1);
            this.tabPage7.Controls.Add(this.button1);
            this.tabPage7.Controls.Add(this.textBox2);
            this.tabPage7.Controls.Add(this.textBox1);
            this.tabPage7.Controls.Add(this.label2);
            this.tabPage7.Location = new System.Drawing.Point(4, 22);
            this.tabPage7.Name = "tabPage7";
            this.tabPage7.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage7.Size = new System.Drawing.Size(152, 191);
            this.tabPage7.TabIndex = 0;
            this.tabPage7.Text = "网络设置";
            // 
            // button2
            // 
            this.button2.Font = new System.Drawing.Font("宋体", 12F);
            this.button2.Location = new System.Drawing.Point(12, 138);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(121, 44);
            this.button2.TabIndex = 5;
            this.button2.Text = "停止服务";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(22, 6);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "本地IP";
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("宋体", 12F);
            this.button1.Location = new System.Drawing.Point(12, 90);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(121, 42);
            this.button1.TabIndex = 4;
            this.button1.Text = "启动服务";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(24, 60);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(100, 21);
            this.textBox2.TabIndex = 7;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(24, 21);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 21);
            this.textBox1.TabIndex = 6;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(22, 45);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "端口号";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.tabControl4);
            this.groupBox3.Font = new System.Drawing.Font("宋体", 12F);
            this.groupBox3.ForeColor = System.Drawing.SystemColors.HotTrack;
            this.groupBox3.Location = new System.Drawing.Point(365, 345);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(376, 304);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "手动控制";
            // 
            // tabControl4
            // 
            this.tabControl4.Controls.Add(this.tabPage9);
            this.tabControl4.Location = new System.Drawing.Point(27, 31);
            this.tabControl4.Name = "tabControl4";
            this.tabControl4.SelectedIndex = 0;
            this.tabControl4.Size = new System.Drawing.Size(329, 263);
            this.tabControl4.TabIndex = 5;
            // 
            // tabPage9
            // 
            this.tabPage9.Controls.Add(this.button5);
            this.tabPage9.Controls.Add(this.button4);
            this.tabPage9.Controls.Add(this.button3);
            this.tabPage9.Controls.Add(this.button8);
            this.tabPage9.Controls.Add(this.button7);
            this.tabPage9.Controls.Add(this.button10);
            this.tabPage9.Controls.Add(this.button11);
            this.tabPage9.Controls.Add(this.button9);
            this.tabPage9.Location = new System.Drawing.Point(4, 26);
            this.tabPage9.Name = "tabPage9";
            this.tabPage9.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage9.Size = new System.Drawing.Size(321, 233);
            this.tabPage9.TabIndex = 0;
            this.tabPage9.Text = "控制";
            this.tabPage9.UseVisualStyleBackColor = true;
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(4, 169);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(88, 58);
            this.button5.TabIndex = 7;
            this.button5.Text = "停车";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(224, 12);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(91, 58);
            this.button4.TabIndex = 6;
            this.button4.Text = "减速";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(7, 12);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(85, 58);
            this.button3.TabIndex = 5;
            this.button3.Text = "加速";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button9
            // 
            this.button9.Font = new System.Drawing.Font("宋体", 20F);
            this.button9.ForeColor = System.Drawing.Color.Red;
            this.button9.Location = new System.Drawing.Point(113, 82);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(91, 70);
            this.button9.TabIndex = 2;
            this.button9.Text = "发车";
            this.button9.UseVisualStyleBackColor = true;
            this.button9.Click += new System.EventHandler(this.button9_Click);
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.tabControl2);
            this.groupBox6.Location = new System.Drawing.Point(203, 12);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(567, 322);
            this.groupBox6.TabIndex = 5;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "状态显示";
            // 
            // tabControl2
            // 
            this.tabControl2.Controls.Add(this.tabPage6);
            this.tabControl2.Location = new System.Drawing.Point(17, 20);
            this.tabControl2.Name = "tabControl2";
            this.tabControl2.SelectedIndex = 0;
            this.tabControl2.Size = new System.Drawing.Size(525, 296);
            this.tabControl2.TabIndex = 0;
            // 
            // tabPage6
            // 
            this.tabPage6.Controls.Add(this.button13);
            this.tabPage6.Controls.Add(this.listBox1);
            this.tabPage6.Location = new System.Drawing.Point(4, 22);
            this.tabPage6.Name = "tabPage6";
            this.tabPage6.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage6.Size = new System.Drawing.Size(517, 270);
            this.tabPage6.TabIndex = 1;
            this.tabPage6.Text = "收发状态";
            this.tabPage6.UseVisualStyleBackColor = true;
            // 
            // button13
            // 
            this.button13.Location = new System.Drawing.Point(408, 235);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(86, 32);
            this.button13.TabIndex = 10;
            this.button13.Text = "清空";
            this.button13.UseVisualStyleBackColor = true;
            this.button13.Click += new System.EventHandler(this.button13_Click);
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.ItemHeight = 12;
            this.listBox1.Location = new System.Drawing.Point(15, 6);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(479, 220);
            this.listBox1.TabIndex = 0;
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 10;
            // 
            // button8
            // 
            this.button8.BackgroundImage = global::OV7725调车上位机.Properties.Resources.left;
            this.button8.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button8.Font = new System.Drawing.Font("宋体", 12F);
            this.button8.Location = new System.Drawing.Point(6, 82);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(86, 67);
            this.button8.TabIndex = 1;
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Click += new System.EventHandler(this.button8_Click);
            // 
            // button7
            // 
            this.button7.BackgroundImage = global::OV7725调车上位机.Properties.Resources.up;
            this.button7.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button7.Font = new System.Drawing.Font("宋体", 12F);
            this.button7.Location = new System.Drawing.Point(113, 12);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(91, 58);
            this.button7.TabIndex = 0;
            this.button7.TextImageRelation = System.Windows.Forms.TextImageRelation.TextAboveImage;
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // button10
            // 
            this.button10.BackgroundImage = global::OV7725调车上位机.Properties.Resources.right;
            this.button10.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button10.Font = new System.Drawing.Font("宋体", 12F);
            this.button10.Location = new System.Drawing.Point(224, 80);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(91, 70);
            this.button10.TabIndex = 3;
            this.button10.UseVisualStyleBackColor = true;
            this.button10.Click += new System.EventHandler(this.button10_Click);
            // 
            // button11
            // 
            this.button11.BackgroundImage = global::OV7725调车上位机.Properties.Resources.down;
            this.button11.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button11.Font = new System.Drawing.Font("宋体", 12F);
            this.button11.Location = new System.Drawing.Point(115, 169);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(89, 58);
            this.button11.TabIndex = 4;
            this.button11.UseVisualStyleBackColor = true;
            this.button11.Click += new System.EventHandler(this.button11_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::OV7725调车上位机.Properties.Resources.QQ图片20170609213913;
            this.pictureBox1.Location = new System.Drawing.Point(12, 356);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(335, 293);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 6;
            this.pictureBox1.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.LightGreen;
            this.ClientSize = new System.Drawing.Size(792, 661);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.groupBox6);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "科沃斯";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.tabControl3.ResumeLayout(false);
            this.tabPage7.ResumeLayout(false);
            this.tabPage7.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.tabControl4.ResumeLayout(false);
            this.tabPage9.ResumeLayout(false);
            this.groupBox6.ResumeLayout(false);
            this.tabControl2.ResumeLayout(false);
            this.tabPage6.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TabControl tabControl2;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TabPage tabPage6;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Button button13;
        private System.Windows.Forms.TabControl tabControl3;
        private System.Windows.Forms.TabPage tabPage7;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.TabControl tabControl4;
        private System.Windows.Forms.TabPage tabPage9;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}

