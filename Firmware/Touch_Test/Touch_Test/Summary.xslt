<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:msxsl="urn:schemas-microsoft-com:xslt" >
  <xsl:template match="/">
    <html>
      <head>
        <style type="text/css">

          .header
          {
          BACKGROUND-COLOR: #BEC0C9;
          BORDER-BOTTOM: #ffffff 1px solid;
          BORDER-LEFT: #ffffff 1px solid;
          BORDER-RIGHT: #ffffff 1px solid;
          BORDER-TOP: #ffffff 1px solid;
          COLOR: #000000;
          FONT-WEIGHT: bold
          }
          .infotable
          {
          TEXT-ALIGN: LEFT;
          BACKGROUND-COLOR: #BEC0C9;
          BORDER-BOTTOM: #ffffff 0px solid;
          BORDER-COLLAPSE: collapse;
          BORDER-LEFT: #ffffff 0px solid;
          BORDER-RIGHT: #ffffff 0px solid;
          BORDER-TOP: #ffffff 0px solid;
          FONT-SIZE: 80%;
          }

          #color1
          {

          BACKGROUND-COLOR: #ffffff;
          }

          #color2
          {

          BACKGROUND-COLOR:#f8f8ff ;
          }


        </style>
      </head>
      <body>
        <table cellspacing="0" width="100%" border="1" bordercolor="white" class="infotable">
          <col width="100" />
          <col width="100" />
          <tr>
            <td nowrap="1" class ="header">Device Information</td>
            <td nowrap="1" class ="header"></td>
          </tr>

          <tr id="color1">
            <td>
              Device Name
            </td>
            <td >
              <xsl:value-of select="SUMMARY/DeviceInformation/DeviceName"/>
            </td>
          </tr>
          <tr id="color2">
            <td >
              Device Variant
            </td>
            <td>
              <xsl:value-of select="SUMMARY/DeviceInformation/DeviceVariant"/>
            </td>
          </tr>

          <tr id="color1">
            <td >
              Technology
            </td>
            <td>
              <xsl:value-of select="SUMMARY/DeviceInformation/Technology"/>
            </td>
          </tr>
          <tr>
            <td nowrap="1" class ="header">Sensor Information</td>
            <td nowrap="1" class ="header"></td>
          </tr>
          <tr id="color1">
            <td>
              Number Of Buttons
            </td>
            <td >
              <xsl:value-of select="SUMMARY/SensorInformation/NumberOfButtons"/>
            </td>
          </tr>
          <tr id="color2">
            <td >
              Number Of Wheels
            </td>
            <td>
              <xsl:value-of select="SUMMARY/SensorInformation/NumberOfWheels"/>
            </td>
          </tr>

          <tr id="color1">
            <td >
              Number Of Sliders
            </td>
            <td>
              <xsl:value-of select="SUMMARY/SensorInformation/NumberOfSliders"/>
            </td>
          </tr>
          <tr>
            <td nowrap="1" class ="header">Channel Information</td>
            <td nowrap="1" class ="header"></td>
          </tr>
          <tr id="color1">
            <td >
              Total Channels Consumed
            </td>
            <td>
              <xsl:value-of select="SUMMARY/ChannelInformation/TotalChannelsConsumed"/>
            </td>
          </tr>
          <tr>
            <td nowrap="1" class ="header">Pin Configuration</td>
            <td nowrap="1" class ="header"></td>
          </tr>
          <tr id="color1">
            <td>
              Available Ports
            </td>
            <td >
              <xsl:value-of select="//SUMMARY/PinConfiguration/AvailablePorts"/>
            </td>
          </tr>
          <tr id="color2">
            <td >
              Total pins Used
            </td>
            <td>
              <xsl:value-of select="//SUMMARY/PinConfiguration/TotalPinsUsed"/>
            </td>
          </tr>

          <tr id="color1">
            <td >
              XY Lines Config 
            </td>
            <td>
              <xsl:value-of select="//SUMMARY/PinConfiguration/PinConfig/XYLinesConfig"/>
            </td>
          </tr>
          <tr id="color2">
            <td >
              X Lines
            </td>
            <td>
              <xsl:value-of select="//SUMMARY/PinConfiguration/PinConfig/XLines"/>
            </td>
          </tr>
          <tr id="color1">
            <td >
              YA Lines
            </td>
            <td>
              <xsl:value-of select="//SUMMARY/PinConfiguration/PinConfig/YALines"/>
            </td>
          </tr>
          <tr id="color2">
            <td >
              YB Lines
            </td>
            <td>
              <xsl:value-of select="//SUMMARY/PinConfiguration/PinConfig/YBLines"/>
            </td>
          </tr>
          <tr id="color1">
            <td >
              SMP Port
            </td>
            <td>
              <xsl:value-of select="//SUMMARY/PinConfiguration/PinConfig/SMPPort"/>
            </td>
          </tr>
          <tr id="color2">
            <td >
              AINO Port
            </td>
            <td>
              <xsl:value-of select="//SUMMARY/PinConfiguration/PinConfig/AINOPort"/>
            </td>
          </tr>
        </table>
        <table cellspacing="0" width="100%" border="1" bordercolor="white" class="infotable">
          <col width="100" />
          <col width="100" />
          <col width="100" />
          <col width="100" />
          <col width="100" />
          <tr>
            <td nowrap="1" class ="header">Name of the sensor</td>
            <td nowrap="1" class ="header">Channels</td>
            <td nowrap="1" class ="header">XPort</td>
            <td nowrap="1" class ="header">YA</td>
            <td nowrap="1" class ="header">YB</td>
          </tr>
          <xsl:for-each select="//SUMMARY/PinConfiguration/PinConfig/Sensors/Sensor">
            <xsl:choose>
              <xsl:when test="(position() mod 2) = 0">
            <tr id="color1">
              <td>
                <xsl:value-of select="@Name"/>
              </td>
                <td>
                  <xsl:value-of select="@ChannelName"/>
                </td>
                <td>
                  <xsl:value-of select="@X"/>
                </td>
                <td>
                  <xsl:value-of select="@YA"/>
                </td>
                <td>
                  <xsl:value-of select="@YB"/>
                </td>
              </tr>
              </xsl:when>
              <xsl:otherwise>
                <tr id="color2">
                  <td>
                    <xsl:value-of select="@Name"/>
                  </td>
                  <td>
                    <xsl:value-of select="@ChannelName"/>
                  </td>
                  <td>
                    <xsl:value-of select="@X"/>
                  </td>
                  <td>
                    <xsl:value-of select="@YA"/>
                  </td>
                  <td>
                    <xsl:value-of select="@YB"/>
                  </td>
                </tr>
              </xsl:otherwise>
            </xsl:choose>
          </xsl:for-each>
        </table>
        <xsl:if test="//SUMMARY/PinConfiguration/DebugInterface/@Enabled='True'">
          <table cellspacing="0" width="100%" border="1" bordercolor="white" class="infotable">
            <col width="100" />
            <col width="100" />
            <tr>
              <td nowrap="1" class ="header">
                Debug Interface- <xsl:value-of select="//SUMMARY/PinConfiguration/DebugInterface/@Type"/>
              </td>
              <td nowrap="1" class ="header">Port Pin</td>
            </tr>
            <xsl:for-each select="//SUMMARY/PinConfiguration/DebugInterface/Port">
              <xsl:choose>
                <xsl:when test="(position() mod 2) = 0">
                  <tr id="color1">
                <td>
                  <xsl:value-of select="@Name"/>
                </td>
                <td>
                  <xsl:value-of select="@PortPin"/>
                </td>
              </tr>
                </xsl:when>
                <xsl:otherwise>
                  <tr id="color2">
                    <td>
                      <xsl:value-of select="@Name"/>
                    </td>
                    <td>
                      <xsl:value-of select="@PortPin"/>
                    </td>
                  </tr>
                 </xsl:otherwise>
            </xsl:choose>
            </xsl:for-each>
            <tr id="color1">
              <td >
                Power Analyzer
              </td>
              <td>
                <xsl:value-of select="SUMMARY/PinConfiguration/DebugInterface/PowerAnalyzer"/>
              </td>
            </tr>
          </table>
        </xsl:if>

        <table cellspacing="0" width="100%" border="1" bordercolor="white" class="infotable">
          <col width="100" />
          <col width="100" />
          <col width="100" />
          <col width="100" />
          <tr>
            <td nowrap="1" class ="header">Memory type</td>
            <td nowrap="1" class ="header">Total</td>
            <td nowrap="1" class ="header">Used</td>
            <td nowrap="1" class ="header">Free</td>
          </tr>
          <tr id="color1">
            <td>
              Data Memory
            </td>
            <td>
              <xsl:value-of select="SUMMARY/MemoryInformation/DataMemory/TotalDataMemory"/>
            </td>
            <td>
              <xsl:value-of select="SUMMARY/MemoryInformation/DataMemory/DataMemoryUsed"/>
            </td>
            <td>
              <xsl:value-of select="SUMMARY/MemoryInformation/DataMemory/DataMemoryFree"/>
            </td>
          </tr>
          <tr id="color2">
            <td>
              Code Memory
            </td>
            <td>
              <xsl:value-of select="SUMMARY/MemoryInformation/CodeMemory/TotalCodeMemory"/>
            </td>
            <td>
              <xsl:value-of select="SUMMARY/MemoryInformation/CodeMemory/CodeMemoryUsed"/>
            </td>
            <td>
              <xsl:value-of select="SUMMARY/MemoryInformation/CodeMemory/CodeMemoryFree"/>
            </td>
          </tr>
        </table>
        <table cellspacing="0" width="100%" border="1" bordercolor="white" class="infotable">
          <col width="169" />
          <col width="100" />
          <tr>
            <td nowrap="1" class ="header">Library Information</td>
          </tr>
          <td nowrap="1" class ="header"></td>
          <tr id="color1">
            <td >
              Tool Chain Name
            </td>
            <td>
              <xsl:value-of select="SUMMARY/LibraryInformation/@ToolChainName"/>
            </td>
          </tr>
          <tr id="color2">
            <td >
              Default Library
            </td>
            <td>
              <xsl:value-of select="SUMMARY/LibraryInformation/DefaultLibrary"/>
            </td>
          </tr>
          <tr>
            <td nowrap="1" class ="header">Other Options</td>
            <td nowrap="1" class ="header"></td>
          </tr>
          <tr id="color1">
            <td >
              Delay Cycle
            </td>
            <td>
              <xsl:value-of select="SUMMARY/OtherOptions/DelayCycle"/>
            </td>
          </tr>
        </table>
      </body>
    </html>
  </xsl:template>
</xsl:stylesheet>


