using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Editor
{
	public class TileImage
	{
		public ImageFile NormalImage;
		public ImageFile SelectedImage;

		public TileImage(ImageFile ni, ImageFile si)
		{
			this.NormalImage = ni;
			this.SelectedImage = si;
		}
	}
}
