using System;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Threading;
using System.Collections;
using System.Drawing;
using System.Data;
using System.IO;
using System.Drawing.Imaging;
using System.Reflection;
using DirectShowLib;
using DirectShowLib.DES;
using ProWrite.Entity.DES;
using ProWrite.Core;
//using RECT=ProWrite.Entity.DES.RECT;

namespace ProWrite.DES
{
    /// <summary>
    /// Time：2008-4-23
    /// Author：Michael
    /// Function：This Class edit transition and effect.
    /// Update：
    /// </summary>
    class DESTransition
    {
        /// <summary>
        /// add Transition on IAMTimelineTrack
        /// 如何把效果加入到层上
        /// 进入Direction设置为True,推出false
        /// </summary>
        public static int SetTransition(ref IAMTimeline m_pTimeline, IAMTimelineTrack pTrac, Guid EffectGUID, bool Direction, long StartTime, long EndTime, Property[] parArr)
        {
            int hr;
            IAMTimelineObj pTransObj;
            IAMTimelineTransable pTransable = (IAMTimelineTransable)pTrac;
            hr = m_pTimeline.CreateEmptyNode(out pTransObj, TimelineMajorType.Transition);
            hr = pTransable.TransAdd(pTransObj);
            pTransObj.SetStartStop(StartTime, EndTime);
            hr = pTransObj.SetSubObjectGUID(EffectGUID);

            IPropertySetter ipro = (IPropertySetter)new PropertySetter();
            if (parArr != null && parArr.Length > 0)
            {
                foreach (Property pro in parArr)
                {
                    if (pro != null)
                        DESHelper.AddParameter(ipro, pro.Name, pro.Value);
                }
            }
            DESHelper.AddParameter(ipro, "Duration", EndTime / DESConsts.UNITS - StartTime / DESConsts.UNITS);
            hr = pTransObj.SetPropertySetter(ipro);

            //Set transition Direction
            if (Direction)
            {
                IAMTimelineTrans pTrans = (IAMTimelineTrans)pTransObj;
                pTrans.SetSwapInputs(true);
            }

            return hr;
        }

        /// <summary>
        /// add Transition on IAMTimelineComp
        /// 设置推出进入效果
        /// </summary>
        public static int SetTransition(ref IAMTimeline m_pTimeline, IAMTimelineComp pComp, Guid EffectGUID, string Direction, long StartTime, long EndTime, Property[] parArr)
        {
            int hr;
            IAMTimelineObj pTransObj;
            IAMTimelineTransable pTransable = (IAMTimelineTransable)pComp;
            hr = m_pTimeline.CreateEmptyNode(out pTransObj, TimelineMajorType.Transition);
            hr = pTransable.TransAdd(pTransObj);
            pTransObj.SetStartStop(StartTime, EndTime);
            hr = pTransObj.SetSubObjectGUID(EffectGUID);

            IPropertySetter ipro = (IPropertySetter)new PropertySetter();
            if (parArr != null && parArr.Length > 0)
            {
                foreach (Property pro in parArr)
                {
                    DESHelper.AddParameter(ipro, pro.Name, pro.Value);
                }
            }
            DESHelper.AddParameter(ipro, "Duration", EndTime / DESConsts.UNITS - StartTime / DESConsts.UNITS);
            hr = pTransObj.SetPropertySetter(ipro);

            //Set transition Direction
            if (Direction.ToLower() == "true")
            {
                IAMTimelineTrans pTrans = (IAMTimelineTrans)pTransObj;
                pTrans.SetSwapInputs(true);
            }

            return hr;
        }

        /// <summary>
        /// Set Transition DxtKey on  IAMTimelineComp
        /// 画中画把黑色设置为透明色
        /// </summary>
        public static int SetDxtKey(ref IAMTimeline m_pTimeline, IAMTimelineComp pComp, long StartTime, long EndTime)
        {
            int hr = 0;
            IAMTimelineObj pTransObj;
            IAMTimelineTransable pTransable;
            pTransable = (IAMTimelineTransable)pComp;

            hr = m_pTimeline.CreateEmptyNode(out pTransObj, TimelineMajorType.Transition);
            hr = pTransable.TransAdd(pTransObj);
            hr = pTransObj.SetSubObjectGUID(DESConsts.GUID_TR_DxtKey);
            pTransObj.SetStartStop(StartTime, EndTime);

            IPropertySetter ipro = (IPropertySetter)new PropertySetter();
            DESHelper.AddParameter(ipro, "KeyType", 0);
            DESHelper.AddParameter(ipro, "RGB", "0x0");
            hr = pTransObj.SetPropertySetter(ipro);
            return hr;
        }

        /// <summary>
        /// Set Compositor on  IAMTimelineComp
        /// </summary>
        public static int SetCompositor(ref IAMTimeline m_pTimeline, IAMTimelineComp pComp, long StartTime, long EndTime, Rectangle Rect)
        {
            int hr = 0;
            IAMTimelineObj pTransObj;
            IAMTimelineTransable pTransable;
            pTransable = (IAMTimelineTransable)pComp;
            hr = m_pTimeline.CreateEmptyNode(out pTransObj, TimelineMajorType.Transition);
            hr = pTransable.TransAdd(pTransObj);
            hr = pTransObj.SetSubObjectGUID(DESConsts.GUID_TR_Compositor);
            pTransObj.SetStartStop(StartTime, EndTime);

            IPropertySetter ipro = (IPropertySetter)new PropertySetter();
            //设置参数到效果
            DESHelper.AddParameter(ipro, "Height", Rect.Height.ToString());
            DESHelper.AddParameter(ipro, "Width", Rect.Width.ToString());
            DESHelper.AddParameter(ipro, "OffsetX", Rect.X.ToString());
            DESHelper.AddParameter(ipro, "OffsetY", Rect.Y.ToString());
            hr = pTransObj.SetPropertySetter(ipro);
            return hr;
        }

        /// <summary>
        /// Set BackGround Effect on IAMTimelineTrack
        /// 显示效果
        /// </summary>
        public static int SetEffect(ref IAMTimeline m_pTimeline, IAMTimelineTrack pTrac, Guid EffectGUID, long starttime, long endtime, Property[] parArr)
        {
            IAMTimelineObj pTransObj;
            int hr = m_pTimeline.CreateEmptyNode(out pTransObj, TimelineMajorType.Effect);
            IAMTimelineEffectable aEffectable = (IAMTimelineEffectable)pTrac;
            pTransObj.SetStartStop(starttime, endtime);
            pTransObj.SetSubObjectGUID(EffectGUID);
            aEffectable.EffectInsBefore(pTransObj, -1);

            IPropertySetter ipro = (IPropertySetter)new PropertySetter();
            if (parArr != null)
            {
                foreach (Property pro in parArr)
                {
                    DESHelper.AddParameter(ipro, pro.Name, pro.Value);
                }
            }
            DESHelper.AddParameter(ipro, "Duration", endtime / DESConsts.UNITS - starttime / DESConsts.UNITS);
            hr = pTransObj.SetPropertySetter(ipro);
            return hr;
        }

        /// <summary>
        /// Set BackGround Effect on IAMTimelineComp
        /// </summary>
        public static int SetEffect(ref IAMTimeline m_pTimeline, IAMTimelineComp pComp, string EffectGUID, long starttime, long endtime, Property[] parArr)
        {
            IAMTimelineObj pTransObj;
            int hr = m_pTimeline.CreateEmptyNode(out pTransObj, TimelineMajorType.Effect);
            IAMTimelineEffectable aEffectable = (IAMTimelineEffectable)pComp;
            pTransObj.SetStartStop(starttime, endtime);
            pTransObj.SetSubObjectGUID(new Guid(EffectGUID.ToUpper()));
            aEffectable.EffectInsBefore(pTransObj, -1);

            IPropertySetter ipro = (IPropertySetter)new PropertySetter();
            if (parArr != null)
            {
                foreach (Property pro in parArr)
                {
                    DESHelper.AddParameter(ipro, pro.Name, pro.Value);
                }
            }
            DESHelper.AddParameter(ipro, "Duration", endtime / DESConsts.UNITS - starttime / DESConsts.UNITS);
            hr = pTransObj.SetPropertySetter(ipro);
            return hr;
        }

        /// <summary>
        /// Set Sign Color on  IAMTimelineComp
        /// 设置sign类型红琥珀rgb
        /// </summary>
        public static int SetSign(ref IAMTimeline m_pTimeline, IAMTimelineComp pComp, long StartTime, long EndTime, SignType pSignType)
        {
            int hr = 0;
            IAMTimelineObj pTransObj;

            hr = m_pTimeline.CreateEmptyNode(out pTransObj, TimelineMajorType.Effect);
            IAMTimelineEffectable aEffectable = (IAMTimelineEffectable)pComp;
            pTransObj.SetStartStop(StartTime, EndTime);
            pTransObj.SetSubObjectGUID(DESConsts.GUID_EF_Sign);
            aEffectable.EffectInsBefore(pTransObj, -1);
            IPropertySetter ipro = (IPropertySetter)new PropertySetter();
            DESHelper.AddParameter(ipro, "AdjustType", pSignType.ToString());
            hr = pTransObj.SetPropertySetter(ipro);
            return hr;
        }

        /// <summary>
        /// 实现画中画颜色偏移
        /// </summary>
        /// <param name="m_pTimeline"></param>
        /// <param name="pComp"></param>
        /// <param name="StartTime"></param>
        /// <param name="EndTime"></param>
        /// <returns></returns>
        public static int SetAlpha(ref IAMTimeline m_pTimeline, IAMTimelineComp pComp, long StartTime, long EndTime)
        {
            int hr = 0;
            IAMTimelineObj pTransObj;

            hr = m_pTimeline.CreateEmptyNode(out pTransObj, TimelineMajorType.Effect);
            IAMTimelineEffectable aEffectable = (IAMTimelineEffectable)pComp;
            pTransObj.SetStartStop(StartTime, EndTime);
            pTransObj.SetSubObjectGUID(DESConsts.GUID_EF_Alpha);
            aEffectable.EffectInsBefore(pTransObj, -1);
            IPropertySetter ipro = (IPropertySetter)new PropertySetter();
            DESHelper.AddParameter(ipro, "alpha", 255);
            hr = pTransObj.SetPropertySetter(ipro);
            return hr;
        }

        /// <summary>
        /// Set Transition Direction on IAMTimelineTrack
        /// </summary>
        public static int SetTransDirection(ref IAMTimeline m_pTimeline, IAMTimelineTrack pTrac, bool Direction, long StartTime, long EndTime)
        {
            int hr;
            IAMTimelineObj pTransObj;
            IAMTimelineTransable pTransable = (IAMTimelineTransable)pTrac;
            hr = m_pTimeline.CreateEmptyNode(out pTransObj, TimelineMajorType.Transition);
            hr = pTransable.TransAdd(pTransObj);
            pTransObj.SetStartStop(StartTime, EndTime);
            IAMTimelineTrans pTrans = (IAMTimelineTrans)pTransObj;
            pTrans.SetSwapInputs(true);
            return hr;
        }

        /// <summary>
        /// Set Text Color Transition
        /// </summary>
        public static int SetColor(IAMTimelineObj pSource1Obj, Color srcColor)
        {
            int hr = 0;
            hr = pSource1Obj.SetSubObjectGUID(DESConsts.GUID_TR_ColorSource);

            IPropertySetter ipro = (IPropertySetter)new PropertySetter();
            DESHelper.AddParameter(ipro, "Color", srcColor.ToArgb());

            pSource1Obj.SetPropertySetter(ipro);
            return hr;
        }

        /// <summary>
        /// Set Sign Color on  IAMTimelineComp
        /// </summary>
        public static int SetPixelate(ref IAMTimeline m_pTimeline, IAMTimelineComp pComp, long StartTime, long EndTime, int Zoom)
        {
            int hr = 0;
            IAMTimelineObj pTransObj;

            hr = m_pTimeline.CreateEmptyNode(out pTransObj, TimelineMajorType.Effect);
            IAMTimelineEffectable aEffectable = (IAMTimelineEffectable)pComp;
            pTransObj.SetStartStop(StartTime, EndTime);
            pTransObj.SetSubObjectGUID(new Guid("F67BBA3B-1980-48CB-92BB-CC826BF458E6"));
            aEffectable.EffectInsBefore(pTransObj, -1);
            IPropertySetter ipro = (IPropertySetter)new PropertySetter();
            DESHelper.AddParameter(ipro, "A2VRatio", Zoom.ToString());
            hr = pTransObj.SetPropertySetter(ipro);
            return hr;
        }
    }
}