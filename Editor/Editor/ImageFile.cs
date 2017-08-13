using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Editor
{
	public class ImageFile
	{
		private string File;

		public ImageFile(string file)
		{
			this.File = file;
		}

		private Image _ImageData;

		public Image ImageData
		{
			get
			{
				if (this._ImageData == null)
					this._ImageData = Bitmap.FromFile(this.File);

				return this._ImageData;
			}
		}
	}
}
