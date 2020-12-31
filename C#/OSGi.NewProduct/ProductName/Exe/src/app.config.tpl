<?xml version="1.0"?>
<configuration>

    <connectionStrings>
        <add providerName ="Acl.Data.OracleClient"  name="Oracle DB1"
             connectionString="User ID=sil2odmsdev;Password=sil2odms;MAX POOL SIZE=20;Connection Timeout=3;Data Source= (DESCRIPTION =
          (ADDRESS_LIST = (ADDRESS = (PROTOCOL = TCP)(HOST = 192.168.10.66)(PORT = 1521))
                          (ADDRESS = (PROTOCOL = TCP)(HOST = 9.20.210.79)(PORT = 1521)))
          (CONNECT_DATA = (SERVICE_NAME = orcl)));"/>

        <add providerName="MySqlConnector"  name="MySQL DB1"
          connectionString="Server=192.168.10.66,9.20.210.79;Database=sil2odmsdev;Uid=sil2odmsdev;Pwd=sil2odmsdev;" />
  </connectionStrings>



  <appSettings>
      <!-- 
            0：从对话框中选择一个节点启动。
           16：节点1。
           18：节点2。
        -->
      <add key="NodeCode" value="0"/>
    
    <!-- 是否启用远程数据库？ -->
    <add key="EnableRemoteDb" value ="false"></add>
  </appSettings>



  <system.diagnostics>
    <trace autoflush="true">
      <listeners >
        <add type="System.Diagnostics.TextWriterTraceListener" traceOutputOptions="DateTime" name="OSGi" initializeData="OSGi.log.txt"/>
      </listeners>
    </trace>
  </system.diagnostics>

  <system.data>
    <DbProviderFactories>
      <clear/>
      <add name="Oracle.ManagedDataAccess.Client"
           invariant="Oracle.ManagedDataAccess.Client"
           description="Oracle Client"
           type="Oracle.ManagedDataAccess.Client.OracleClientFactory,Oracle.ManagedDataAccess"/>
      <add name="System.Data.SQLite"
           invariant="System.Data.SQLite"
           description="System.Data.SQLite"
           type="System.Data.SQLite.SQLiteFactory,System.Data.SQLite"/>
      <add name="System.Data.OracleClient"
          invariant="System.Data.OracleClient"
          description="System.Data.OracleClient"
          type="System.Data.OracleClient.OracleClientFactory,System.Data.OracleClient"/>
      <add name="Acl.Data.OracleClient"
           invariant="Acl.Data.OracleClient"
           description="Acl.Data.OracleClient"
           type="Acl.Data.OracleClient.OracleClientFactory,Acl.Data"/>
        <add name="MySqlConnector"
            invariant="MySqlConnector"
            description=".Net Framework Data Provider for MySQL"
            type="MySql.Data.MySqlClient.MySqlClientFactory,MySqlConnector" />
    </DbProviderFactories>
  </system.data>

  <startup useLegacyV2RuntimeActivationPolicy="true">
    <supportedRuntime version="v4.0" sku=".NETFramework,Version=v4.5"/>
  </startup>

  <runtime>
    <!--是否捕获破坏性异常（SEH异常等）-->
    <legacyCorruptedStateExceptionsPolicy enabled="true" />
    <assemblyBinding xmlns="urn:schemas-microsoft-com:asm.v1">
      <probing privatePath="libs" />
    </assemblyBinding>
  </runtime>

</configuration>
