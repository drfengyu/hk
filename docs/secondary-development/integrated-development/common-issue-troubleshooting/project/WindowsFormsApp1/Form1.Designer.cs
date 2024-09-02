namespace WindowsFormsApp1
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
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.mvdRenderActivex1 = new VisionDesigner.MVDRenderActivex();
            this.SuspendLayout();
            // 
            // mvdRenderActivex1
            // 
            this.mvdRenderActivex1.EnableRetainShape = false;
            this.mvdRenderActivex1.InteractType = VisionDesigner.MVDRenderInteractType.Standard;
            this.mvdRenderActivex1.Location = new System.Drawing.Point(70, 47);
            this.mvdRenderActivex1.MenuLanguage = VisionDesigner.MVDRenderMenuLangType.Default;
            this.mvdRenderActivex1.Name = "mvdRenderActivex1";
            this.mvdRenderActivex1.Size = new System.Drawing.Size(435, 308);
            this.mvdRenderActivex1.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.mvdRenderActivex1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private VisionDesigner.MVDRenderActivex mvdRenderActivex1;
    }
}

