namespace Editor
{
	partial class LineInputWin
	{
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		/// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows フォーム デザイナで生成されたコード

		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		private void InitializeComponent()
		{
			this.InputLine = new System.Windows.Forms.TextBox();
			this.OKBtn = new System.Windows.Forms.Button();
			this.Prompt = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// InputLine
			// 
			this.InputLine.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.InputLine.Font = new System.Drawing.Font("ＭＳ ゴシック", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.InputLine.Location = new System.Drawing.Point(12, 48);
			this.InputLine.Name = "InputLine";
			this.InputLine.Size = new System.Drawing.Size(336, 23);
			this.InputLine.TabIndex = 1;
			this.InputLine.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.InputLine_KeyPress);
			// 
			// OKBtn
			// 
			this.OKBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.OKBtn.Location = new System.Drawing.Point(271, 85);
			this.OKBtn.Name = "OKBtn";
			this.OKBtn.Size = new System.Drawing.Size(77, 33);
			this.OKBtn.TabIndex = 2;
			this.OKBtn.Text = "閉じる";
			this.OKBtn.UseVisualStyleBackColor = true;
			this.OKBtn.Click += new System.EventHandler(this.OKBtn_Click);
			// 
			// Prompt
			// 
			this.Prompt.AutoSize = true;
			this.Prompt.Font = new System.Drawing.Font("ＭＳ ゴシック", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.Prompt.Location = new System.Drawing.Point(20, 20);
			this.Prompt.Name = "Prompt";
			this.Prompt.Size = new System.Drawing.Size(40, 16);
			this.Prompt.TabIndex = 0;
			this.Prompt.Text = "----";
			// 
			// LineInputWin
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(360, 130);
			this.Controls.Add(this.Prompt);
			this.Controls.Add(this.OKBtn);
			this.Controls.Add(this.InputLine);
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "LineInputWin";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "LineInputWin";
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.LineInputWin_FormClosed);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox InputLine;
		private System.Windows.Forms.Button OKBtn;
		private System.Windows.Forms.Label Prompt;
	}
}
