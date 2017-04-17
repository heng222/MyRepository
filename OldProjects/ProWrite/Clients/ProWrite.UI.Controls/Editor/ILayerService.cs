using System;
using System.Collections.Generic;
using System.Text;

using ProWrite.Entity.Shape;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Editor
{
    public interface ILayerService
    {
        void AddLayer(ShapeType shapeType, ShapeAddMode mode);
        void AddLayer(ShapeBase shape, ShapeAddMode mode);
        void AddLayer(LayerControl frameLayer, ShapeAddMode mode);

        void RemoveLayer(ShapeBase shape);
        void RemoveLayer(LayerControl frameLayer);
        void RemoveLayer();

        void MoveLayers(LayerControl source, LayerControl dest);
        void MoveLayers(LayerControl source, LayerDirection direction);
        void MoveForward(LayerControl source);
        void MoveBack(LayerControl source);
        void MoveFirst();
        void MoveFirst(ShapeBase shape);
        void MoveFirst(LayerControl source);
        void MoveLast();
        void MoveLast(ShapeBase shape);
        void MoveLast(LayerControl source);
    }
}
