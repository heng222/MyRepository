using System;

namespace ProWrite.UFE.Entity
{
    [Serializable]
    public struct ContentIDType
    {

        public string CXCUniqueIdentifier;
        public string FileType;
        public string HumanReadableName;
        public string LibraryName;
        public string ProWriteIdentifier;

        public FileActionType Create;
        public FileActionType Modify;
        public FileActionType Upload;
    }
}
