using System;
using System.ComponentModel;
namespace ProWrite.Entity.DES.Effect
{
    public class EffectId
    {
        public Guid Guid { get;private set;}
        public string Name { get;private set;}

        private EffectId (){}

        public static readonly EffectId
            None = new EffectId { Name = "None" },
            Bijou = new EffectId { Guid = new Guid("A4B54A75-6E38-4312-B5E9-C9950EE98141"), Name = "Bijou" },
            BlackHole = new EffectId { Guid = new Guid("B058D4C2-1D75-4226-8C8C-66CCD2802735"), Name = "BlackHole" },
            Bounce = new EffectId { Guid = new Guid("A631D229-A165-4db7-B28D-32D4CE2CA42C"), Name = "Bounce" },
            Coalesce = new EffectId { Guid = new Guid("C83F0057-B7F1-44E9-9EBF-648A57B3BE7E"), Name = "Coalesce" },
            Copy = new EffectId { Guid = Guid.Empty, Name = "Copy" },
            Fade = new EffectId { Guid = new Guid("16B280C5-EE70-11D1-9066-00C04FD9189D"), Name = "Fade" },
            Filter = new EffectId { Guid = new Guid("D0AA7BDD-F81F-48ca-B914-5DD196EFC398"), Name = "Filter" },
            Flash = new EffectId { Guid = new Guid("66CAB342-DDEF-4E2C-B407-19DA2D41A938"), Name = "Flash" },
            Interleave = new EffectId { Guid = new Guid("098EA7F1-DA86-48ca-BB90-3C730BC32AD7"), Name = "Interleave" },
            Line = new EffectId { Guid = new Guid("F51A5AD6-D26C-4c90-BCA5-7698EF5BD317"), Name = "Line" },
            MultiWipe = new EffectId { Guid = new Guid("1105251F-2672-466D-9D8C-DAD7F90AA0C2"), Name = "MultiWipe" },
            Radar = new EffectId { Guid = new Guid("3D75C64D-6706-4DC0-A287-BC8695676DAD"), Name = "Radar" },
            Rain = new EffectId { Guid = new Guid("158BBBD4-B83C-4168-9598-6D30E99530DC"), Name = "Rain" },
            Slide = new EffectId { Guid = new Guid("86E33B61-4FDF-4514-95D4-8BCDB5C33D1C"), Name = "Slide" },

            Slot = new EffectId { Guid = new Guid("4615B371-8A88-4141-8CF5-3993386EAF69"), Name = "Slot" },
            Snow = new EffectId { Guid = new Guid("632BB53B-C02D-4AB1-B041-A14F524812EF"), Name = "Snow" },
            Sparkle = new EffectId { Guid = new Guid("9D15677F-1972-41A9-8573-2D037055743C"), Name = "Sparkle" },
            Travel = new EffectId { Guid = new Guid("0740D73C-0676-4AFC-BEB9-07F3AE6A8FA3"), Name = "Travel" },
            Venetian = new EffectId { Guid = new Guid("A43598F6-C2FC-4FE3-816C-9599E6D0CD9B"), Name = "Venetian" },
            WrapAround = new EffectId { Guid = new Guid("89BDCC9F-96B6-426F-B6CC-FEE51C3C818D"), Name = "WrapAround" },
            Wipe = new EffectId { Guid = new Guid("87A66F87-E9BE-47DF-A5AD-4C7FF1582079"), Name = "Wipe" }
            ;


    }
}