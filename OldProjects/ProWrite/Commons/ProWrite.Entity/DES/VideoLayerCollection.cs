using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using ProWrite.Core;
using ProWrite.Entity.DES;

namespace ProWrite.Entity.DES
{
	[Serializable]
	public class VideoLayerCollection : List<Layer>
	{
        private string _name = "";
        public string Name
        {
            get { return _name; }
            set
            {
                if (value != _name)
                {
                    _name = value;
                }
            }
        }

        private bool _MasterLayerVisual = false;
        public bool MasterLayerVisual
        {
            get { return _MasterLayerVisual; }
            set
            {
                if (value != MasterLayerVisual)
                {
                    _MasterLayerVisual = value;
                }
            }
        }

		private long _PlayLength = 0;
		public long PlayLength
		{
			get { return _PlayLength; }
			set
			{
				if (value != PlayLength)
				{
					_PlayLength = value;
				}
			}
		}

        private SignType _SignType;
        public SignType SignType
        {
            get { return _SignType; }
            set
            {
                if (value != _SignType)
                {
                    _SignType = value;
                }
            }
        }

        private int _Zoom = 1;
        public int Zoom
        {
            get { return _Zoom; }
            set
            {
                if (value != _Zoom)
                {
                    _Zoom = value;
                }
            }
        }

        private Color _BackColor = Color.Black;
        public Color BackColor
        {
            get { return _BackColor; }
            set
            {
                if (value != _BackColor)
                {
                    _BackColor = value;
                }
            }
        }

        private LayerEffect _EmphasisEffect = null;
        public LayerEffect EmphasisEffect
        {
            get { return _EmphasisEffect; }
            set
            {
                if (value != EmphasisEffect)
                {
                    _EmphasisEffect = value;
                }
            }
        }

        private Size _VideoSize = Size.Empty;
        public Size VideoSize
        {
            get { return _VideoSize; }
            set
            {
                if (value != _VideoSize)
                {
                    _VideoSize = value;
                }
            }
        }

        private string _ParentName = "";
        public string ParentName
        {
            get { return _ParentName; }
            set
            {
                if (value != _ParentName)
                {
                    _ParentName = value;
                }
            }
        }

        /// <summary>
        /// Indicate if the layer is the new items in playlist
        /// </summary>
        public bool IsNewStart { get; set; }

        /// <summary>
        /// Indicate the parent group type, 
        /// Message : null
        /// items in Playlist : Playlist
        /// items in TimeSliceGroup : TimeSliceGroup
        /// </summary>
        public LibraryType? GroupType { get; set; }
	}
}