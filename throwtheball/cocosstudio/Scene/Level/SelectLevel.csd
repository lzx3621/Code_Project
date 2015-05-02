<GameProjectFile>
  <PropertyGroup Type="Layer" Name="SelectLevel" ID="87e61a09-bbf3-4ea4-adf4-a4cd367df9df" Version="2.2.1.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Layer" FrameEvent="" Tag="31" ctype="LayerObjectData">
        <Position X="0.0000" Y="0.0000" />
        <Scale ScaleX="1.0000" ScaleY="1.0000" />
        <AnchorPoint />
        <CColor A="255" R="255" G="255" B="255" />
        <Size X="720.0000" Y="1280.0000" />
        <PrePosition X="0.0000" Y="0.0000" />
        <PreSize X="0.0000" Y="0.0000" />
        <Children>
          <NodeObjectData Name="background" ActionTag="-1564980880" FrameEvent="" Tag="48" Scale9Width="720" Scale9Height="1280" ctype="ImageViewObjectData">
            <Position X="360.0000" Y="640.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="720.0000" Y="1280.0000" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="Normal" Path="Scene/Level/background.png" />
          </NodeObjectData>
          <NodeObjectData Name="CheckGroup" ActionTag="91029205" FrameEvent="" Tag="73" LeftMargin="42.0000" RightMargin="42.0000" TopMargin="29.0043" BottomMargin="562.9957" TouchEnable="True" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="636" Scale9Height="688" ctype="PanelObjectData">
            <Position X="360.0000" Y="906.9957" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="636.0000" Y="688.0000" />
            <PrePosition X="0.5000" Y="0.7086" />
            <PreSize X="0.8833" Y="0.5375" />
            <Children>
              <NodeObjectData Name="CheckBox_waiter" ActionTag="-406510381" FrameEvent="" Tag="50" LeftMargin="-194.0000" RightMargin="-194.0000" TopMargin="-33.9489" BottomMargin="465.9489" TouchEnable="True" ctype="CheckBoxObjectData">
                <Position X="318.0000" Y="596.1505" />
                <Scale ScaleX="0.5000" ScaleY="0.5000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5086" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="1024.0000" Y="256.0000" />
                <PrePosition X="0.5000" Y="0.8665" />
                <PreSize X="1.4222" Y="0.2000" />
                <Children>
                  <NodeObjectData Name="waiter_best" ActionTag="-87884883" VisibleForFrame="False" FrameEvent="" Tag="51" LeftMargin="37.3090" RightMargin="815.6910" TopMargin="46.5000" BottomMargin="38.5000" Scale9Width="171" Scale9Height="171" ctype="ImageViewObjectData">
                    <Position X="122.8090" Y="124.0000" />
                    <Scale ScaleX="1.5000" ScaleY="1.5000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="171.0000" Y="171.0000" />
                    <PrePosition X="0.1199" Y="0.4844" />
                    <PreSize X="0.1670" Y="0.6680" />
                    <FileData Type="Normal" Path="Scene/Level/best.png" />
                  </NodeObjectData>
                  <NodeObjectData Name="waiter_title" ActionTag="749890961" VisibleForFrame="False" FrameEvent="" Tag="52" LeftMargin="376.0000" RightMargin="376.0000" TopMargin="112.0000" BottomMargin="76.0000" FontSize="68" LabelText="饭店小二" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ctype="TextObjectData">
                    <Position X="512.0000" Y="110.0000" />
                    <Scale ScaleX="2.0000" ScaleY="2.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="64" G="36" B="7" />
                    <Size X="272.0000" Y="68.0000" />
                    <PrePosition X="0.5000" Y="0.4297" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FontResource Type="Normal" Path="Font/Casper.ttf" />
                  </NodeObjectData>
                  <NodeObjectData Name="waiter" ActionTag="529709342" FrameEvent="" Tag="53" LeftMargin="849.5000" RightMargin="73.5000" TopMargin="67.5000" BottomMargin="51.5000" ctype="SpriteObjectData">
                    <Position X="900.0000" Y="120.0000" />
                    <Scale ScaleX="1.7000" ScaleY="1.7000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="101.0000" Y="137.0000" />
                    <PrePosition X="0.8789" Y="0.4688" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="MarkedSubImage" Path="Sprite/hero/waiter.png" Plist="Sprite/hero/hero.plist" />
                  </NodeObjectData>
                  <NodeObjectData Name="waiter_disable" ActionTag="-1906615051" FrameEvent="" Tag="42" Scale9Width="576" Scale9Height="145" ctype="ImageViewObjectData">
                    <Position X="512.0000" Y="128.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="1024.0000" Y="256.0000" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="1.4222" Y="0.2000" />
                    <Children>
                      <NodeObjectData Name="waiter_disable_ico" ActionTag="-1213984505" FrameEvent="" Tag="54" LeftMargin="849.5000" RightMargin="73.5000" TopMargin="67.5000" BottomMargin="51.5000" ctype="SpriteObjectData">
                        <Position X="900.0000" Y="120.0000" />
                        <Scale ScaleX="1.7000" ScaleY="1.7000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <Size X="101.0000" Y="137.0000" />
                        <PrePosition X="0.8789" Y="0.4688" />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="MarkedSubImage" Path="Sprite/hero/waiter_disable.png" Plist="Sprite/hero/hero.plist" />
                      </NodeObjectData>
                    </Children>
                    <FileData Type="Normal" Path="Scene/Level/cable.png" />
                  </NodeObjectData>
                </Children>
                <NormalBackFileData Type="Normal" Path="Scene/Level/Level_Active_n.png" />
                <PressedBackFileData Type="Normal" Path="Scene/Level/Level_Active_p.png" />
                <DisableBackFileData Type="Normal" Path="Scene/Level/Level_Active_n.png" />
                <NodeNormalFileData Type="Normal" Path="Common/ok.png" />
                <NodeDisableFileData Type="Normal" Path="Scene/Level/Level_Active_n.png" />
              </NodeObjectData>
              <NodeObjectData Name="CheckBox_scholar" ActionTag="758629706" FrameEvent="" Tag="55" LeftMargin="-194.0000" RightMargin="-194.0000" TopMargin="133.4634" BottomMargin="298.5366" TouchEnable="True" ctype="CheckBoxObjectData">
                <Position X="318.0000" Y="428.7382" />
                <Scale ScaleX="0.5000" ScaleY="0.5000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5086" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="1024.0000" Y="256.0000" />
                <PrePosition X="0.5000" Y="0.6232" />
                <PreSize X="1.4222" Y="0.2000" />
                <Children>
                  <NodeObjectData Name="scholar_best" ActionTag="-378473251" VisibleForFrame="False" FrameEvent="" Tag="56" LeftMargin="37.3090" RightMargin="815.6910" TopMargin="46.4997" BottomMargin="38.5003" Scale9Width="171" Scale9Height="171" ctype="ImageViewObjectData">
                    <Position X="122.8090" Y="124.0003" />
                    <Scale ScaleX="1.5000" ScaleY="1.5000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="171.0000" Y="171.0000" />
                    <PrePosition X="0.1199" Y="0.4844" />
                    <PreSize X="0.1670" Y="0.6680" />
                    <FileData Type="Normal" Path="Scene/Level/best.png" />
                  </NodeObjectData>
                  <NodeObjectData Name="scholar_title" ActionTag="-1263288669" VisibleForFrame="False" FrameEvent="" Tag="57" LeftMargin="373.0000" RightMargin="373.0000" TopMargin="112.0000" BottomMargin="76.0000" FontSize="68" LabelText="儒雅书生" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ctype="TextObjectData">
                    <Position X="512.0000" Y="110.0000" />
                    <Scale ScaleX="2.0000" ScaleY="2.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="64" G="36" B="7" />
                    <Size X="278.0000" Y="68.0000" />
                    <PrePosition X="0.5000" Y="0.4297" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FontResource Type="Normal" Path="Font/Casper.ttf" />
                  </NodeObjectData>
                  <NodeObjectData Name="scholar" ActionTag="-200357754" FrameEvent="" Tag="58" LeftMargin="846.0000" RightMargin="70.0000" TopMargin="68.0000" BottomMargin="52.0000" ctype="SpriteObjectData">
                    <Position X="900.0000" Y="120.0000" />
                    <Scale ScaleX="1.7000" ScaleY="1.7000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="108.0000" Y="136.0000" />
                    <PrePosition X="0.8789" Y="0.4688" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="MarkedSubImage" Path="Sprite/hero/scholar.png" Plist="Sprite/hero/hero.plist" />
                  </NodeObjectData>
                  <NodeObjectData Name="scholar_disable" ActionTag="1395010180" FrameEvent="" Tag="43" Scale9Width="576" Scale9Height="145" ctype="ImageViewObjectData">
                    <Position X="512.0000" Y="128.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="1024.0000" Y="256.0000" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="1.4222" Y="0.2000" />
                    <Children>
                      <NodeObjectData Name="scholar_disable_ico" ActionTag="-1390788774" FrameEvent="" Tag="59" LeftMargin="846.0000" RightMargin="70.0000" TopMargin="68.0000" BottomMargin="52.0000" ctype="SpriteObjectData">
                        <Position X="900.0000" Y="120.0000" />
                        <Scale ScaleX="1.7000" ScaleY="1.7000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <Size X="108.0000" Y="136.0000" />
                        <PrePosition X="0.8789" Y="0.4688" />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="MarkedSubImage" Path="Sprite/hero/scholar_disable.png" Plist="Sprite/hero/hero.plist" />
                      </NodeObjectData>
                    </Children>
                    <FileData Type="Normal" Path="Scene/Level/cable.png" />
                  </NodeObjectData>
                </Children>
                <NormalBackFileData Type="Normal" Path="Scene/Level/Level_Active_n.png" />
                <PressedBackFileData Type="Normal" Path="Scene/Level/Level_Active_p.png" />
                <DisableBackFileData Type="Normal" Path="Scene/Level/Level_Active_n.png" />
                <NodeNormalFileData Type="Normal" Path="Common/ok.png" />
                <NodeDisableFileData Type="Normal" Path="Scene/Level/Level_Active_n.png" />
              </NodeObjectData>
              <NodeObjectData Name="CheckBox_cateran" ActionTag="1481572655" FrameEvent="" Tag="60" LeftMargin="-194.0000" RightMargin="-194.0000" TopMargin="300.8730" BottomMargin="131.1270" TouchEnable="True" ctype="CheckBoxObjectData">
                <Position X="318.0000" Y="261.3286" />
                <Scale ScaleX="0.5000" ScaleY="0.5000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5086" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="1024.0000" Y="256.0000" />
                <PrePosition X="0.5000" Y="0.3798" />
                <PreSize X="1.4222" Y="0.2000" />
                <Children>
                  <NodeObjectData Name="cateran_best" ActionTag="931229040" VisibleForFrame="False" FrameEvent="" Tag="61" LeftMargin="37.3090" RightMargin="815.6910" TopMargin="46.5000" BottomMargin="38.5000" Scale9Width="171" Scale9Height="171" ctype="ImageViewObjectData">
                    <Position X="122.8090" Y="124.0000" />
                    <Scale ScaleX="1.5000" ScaleY="1.5000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="171.0000" Y="171.0000" />
                    <PrePosition X="0.1199" Y="0.4844" />
                    <PreSize X="0.1670" Y="0.6680" />
                    <FileData Type="Normal" Path="Scene/Level/best.png" />
                  </NodeObjectData>
                  <NodeObjectData Name="cateran_title" ActionTag="1378695854" VisibleForFrame="False" FrameEvent="" Tag="62" LeftMargin="376.0000" RightMargin="376.0000" TopMargin="112.0000" BottomMargin="76.0000" FontSize="68" LabelText="山贼大王" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ctype="TextObjectData">
                    <Position X="512.0000" Y="110.0000" />
                    <Scale ScaleX="2.0000" ScaleY="2.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="64" G="36" B="7" />
                    <Size X="272.0000" Y="68.0000" />
                    <PrePosition X="0.5000" Y="0.4297" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FontResource Type="Normal" Path="Font/Casper.ttf" />
                  </NodeObjectData>
                  <NodeObjectData Name="cateran" ActionTag="-295569373" FrameEvent="" Tag="63" LeftMargin="830.5000" RightMargin="54.5000" TopMargin="73.5000" BottomMargin="57.5000" ctype="SpriteObjectData">
                    <Position X="900.0000" Y="120.0000" />
                    <Scale ScaleX="1.7000" ScaleY="1.7000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="139.0000" Y="125.0000" />
                    <PrePosition X="0.8789" Y="0.4688" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="MarkedSubImage" Path="Sprite/hero/cateran.png" Plist="Sprite/hero/hero.plist" />
                  </NodeObjectData>
                  <NodeObjectData Name="cateran_disable" ActionTag="155183187" FrameEvent="" Tag="44" Scale9Width="576" Scale9Height="145" ctype="ImageViewObjectData">
                    <Position X="512.0000" Y="128.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="1024.0000" Y="256.0000" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="1.0000" Y="1.0000" />
                    <Children>
                      <NodeObjectData Name="cateran_disable_ico" ActionTag="-2110885798" FrameEvent="" Tag="64" LeftMargin="830.5000" RightMargin="54.5000" TopMargin="73.5000" BottomMargin="57.5000" ctype="SpriteObjectData">
                        <Position X="900.0000" Y="120.0000" />
                        <Scale ScaleX="1.7000" ScaleY="1.7000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <Size X="139.0000" Y="125.0000" />
                        <PrePosition X="0.8789" Y="0.4688" />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="MarkedSubImage" Path="Sprite/hero/cateran_disable.png" Plist="Sprite/hero/hero.plist" />
                      </NodeObjectData>
                    </Children>
                    <FileData Type="Normal" Path="Scene/Level/cable.png" />
                  </NodeObjectData>
                </Children>
                <NormalBackFileData Type="Normal" Path="Scene/Level/Level_Active_n.png" />
                <PressedBackFileData Type="Normal" Path="Scene/Level/Level_Active_p.png" />
                <DisableBackFileData Type="Normal" Path="Scene/Level/Level_Active_n.png" />
                <NodeNormalFileData Type="Normal" Path="Common/ok.png" />
                <NodeDisableFileData Type="Normal" Path="Scene/Level/Level_Active_n.png" />
              </NodeObjectData>
              <NodeObjectData Name="CheckBox_general" ActionTag="975900914" FrameEvent="" Tag="65" LeftMargin="-194.0000" RightMargin="-194.0000" TopMargin="468.2832" BottomMargin="-36.2832" TouchEnable="True" ctype="CheckBoxObjectData">
                <Position X="318.0000" Y="93.9184" />
                <Scale ScaleX="0.5000" ScaleY="0.5000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5086" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="1024.0000" Y="256.0000" />
                <PrePosition X="0.5000" Y="0.1365" />
                <PreSize X="1.4222" Y="0.2000" />
                <Children>
                  <NodeObjectData Name="general_best" ActionTag="-916246092" VisibleForFrame="False" FrameEvent="" Tag="66" LeftMargin="37.3090" RightMargin="815.6910" TopMargin="46.5000" BottomMargin="38.5000" Scale9Width="171" Scale9Height="171" ctype="ImageViewObjectData">
                    <Position X="122.8090" Y="124.0000" />
                    <Scale ScaleX="1.5000" ScaleY="1.5000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="171.0000" Y="171.0000" />
                    <PrePosition X="0.1199" Y="0.4844" />
                    <PreSize X="0.1670" Y="0.6680" />
                    <FileData Type="Normal" Path="Scene/Level/best.png" />
                  </NodeObjectData>
                  <NodeObjectData Name="general_title" ActionTag="-186774654" VisibleForFrame="False" FrameEvent="" Tag="67" LeftMargin="376.0000" RightMargin="376.0000" TopMargin="112.0000" BottomMargin="76.0000" FontSize="68" LabelText="神勇将军" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ctype="TextObjectData">
                    <Position X="512.0000" Y="110.0000" />
                    <Scale ScaleX="2.0000" ScaleY="2.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="64" G="36" B="7" />
                    <Size X="272.0000" Y="68.0000" />
                    <PrePosition X="0.5000" Y="0.4297" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FontResource Type="Normal" Path="Font/Casper.ttf" />
                  </NodeObjectData>
                  <NodeObjectData Name="general" ActionTag="-1892271972" FrameEvent="" Tag="68" LeftMargin="849.5000" RightMargin="73.5000" TopMargin="67.5000" BottomMargin="51.5000" ctype="SpriteObjectData">
                    <Position X="900.0000" Y="120.0000" />
                    <Scale ScaleX="1.7000" ScaleY="1.7000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="101.0000" Y="137.0000" />
                    <PrePosition X="0.8789" Y="0.4688" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="MarkedSubImage" Path="Sprite/hero/general.png" Plist="Sprite/hero/hero.plist" />
                  </NodeObjectData>
                  <NodeObjectData Name="general_disable" ActionTag="2036123657" FrameEvent="" Tag="45" Scale9Width="576" Scale9Height="145" ctype="ImageViewObjectData">
                    <Position X="512.0000" Y="128.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="1024.0000" Y="256.0000" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="1.0000" Y="1.0000" />
                    <Children>
                      <NodeObjectData Name="general_disable_ico" ActionTag="290478950" FrameEvent="" Tag="69" LeftMargin="847.0000" RightMargin="71.0000" TopMargin="67.5000" BottomMargin="51.5000" ctype="SpriteObjectData">
                        <Position X="900.0000" Y="120.0000" />
                        <Scale ScaleX="1.7000" ScaleY="1.7000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <Size X="106.0000" Y="137.0000" />
                        <PrePosition X="0.8789" Y="0.4688" />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="MarkedSubImage" Path="Sprite/hero/general_disable.png" Plist="Sprite/hero/hero.plist" />
                      </NodeObjectData>
                    </Children>
                    <FileData Type="Normal" Path="Scene/Level/cable.png" />
                  </NodeObjectData>
                </Children>
                <NormalBackFileData Type="Normal" Path="Scene/Level/Level_Active_n.png" />
                <PressedBackFileData Type="Normal" Path="Scene/Level/Level_Active_p.png" />
                <DisableBackFileData Type="Normal" Path="Scene/Level/Level_Active_n.png" />
                <NodeNormalFileData Type="Normal" Path="Common/ok.png" />
                <NodeDisableFileData Type="Normal" Path="Scene/Level/Level_Active_n.png" />
              </NodeObjectData>
            </Children>
            <FileData Type="Normal" Path="Scene/Level/bottom.png" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </NodeObjectData>
          <NodeObjectData Name="Photo" ActionTag="-1764517204" FrameEvent="" Tag="52" LeftMargin="232.0000" RightMargin="232.0000" TopMargin="1042.0000" BottomMargin="-18.0000" ctype="SpriteObjectData">
            <Position X="360.0000" Y="110.0000" />
            <Scale ScaleX="0.7000" ScaleY="0.7000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="256.0000" Y="256.0000" />
            <PrePosition X="0.5000" Y="0.0859" />
            <PreSize X="0.0000" Y="0.0000" />
            <Children>
              <NodeObjectData Name="title_photo" ActionTag="-1449576366" FrameEvent="" Tag="53" LeftMargin="80.5000" RightMargin="80.5000" TopMargin="108.5000" BottomMargin="108.5000" Scale9Width="95" Scale9Height="39" ctype="ImageViewObjectData">
                <Position X="128.0000" Y="128.0000" />
                <Scale ScaleX="1.3000" ScaleY="1.3000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="95.0000" Y="39.0000" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.3711" Y="0.1523" />
                <FileData Type="Normal" Path="Scene/Level/icon.png" />
              </NodeObjectData>
              <NodeObjectData Name="new_title" ActionTag="1303961688" FrameEvent="" Tag="54" LeftMargin="11.0294" RightMargin="167.9706" TopMargin="8.5896" BottomMargin="177.4104" Scale9Width="77" Scale9Height="70" ctype="ImageViewObjectData">
                <Position X="49.5294" Y="212.4104" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="77.0000" Y="70.0000" />
                <PrePosition X="0.1935" Y="0.8297" />
                <PreSize X="0.3008" Y="0.2734" />
                <FileData Type="Normal" Path="Scene/Level/new.png" />
              </NodeObjectData>
            </Children>
            <FileData Type="Normal" Path="Common/circle.png" />
          </NodeObjectData>
          <NodeObjectData Name="store" ActionTag="-1663947586" FrameEvent="" Tag="55" LeftMargin="472.0000" RightMargin="-8.0000" TopMargin="1042.0000" BottomMargin="-18.0000" ctype="SpriteObjectData">
            <Position X="600.0000" Y="110.0000" />
            <Scale ScaleX="0.7000" ScaleY="0.7000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="256.0000" Y="256.0000" />
            <PrePosition X="0.8333" Y="0.0859" />
            <PreSize X="0.0000" Y="0.0000" />
            <Children>
              <NodeObjectData Name="ico_store" ActionTag="906885101" FrameEvent="" Tag="56" LeftMargin="64.0000" RightMargin="64.0000" TopMargin="64.0000" BottomMargin="64.0000" Scale9Width="128" Scale9Height="128" ctype="ImageViewObjectData">
                <Position X="128.0000" Y="128.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="128.0000" Y="128.0000" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.1778" Y="0.1000" />
                <FileData Type="Normal" Path="Common/store.png" />
              </NodeObjectData>
            </Children>
            <FileData Type="Normal" Path="Common/circle.png" />
          </NodeObjectData>
          <NodeObjectData Name="back" ActionTag="165555692" FrameEvent="" Tag="59" LeftMargin="-8.0000" RightMargin="472.0000" TopMargin="1042.0000" BottomMargin="-18.0000" TouchEnable="True" FontSize="14" ButtonText="" Scale9Enable="True" Scale9Width="256" Scale9Height="256" ctype="ButtonObjectData">
            <Position X="120.0000" Y="110.0000" />
            <Scale ScaleX="0.7000" ScaleY="0.7000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="256.0000" Y="256.0000" />
            <PrePosition X="0.1667" Y="0.0859" />
            <PreSize X="0.3556" Y="0.2000" />
            <Children>
              <NodeObjectData Name="ico_back" ActionTag="2077871627" FrameEvent="" Tag="60" LeftMargin="64.0000" RightMargin="64.0000" TopMargin="64.0000" BottomMargin="64.0000" Scale9Width="128" Scale9Height="128" ctype="ImageViewObjectData">
                <Position X="128.0000" Y="128.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="128.0000" Y="128.0000" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.5000" Y="0.5000" />
                <FileData Type="Normal" Path="Common/back.png" />
              </NodeObjectData>
            </Children>
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" />
            <PressedFileData Type="Normal" Path="Common/circle.png" />
            <NormalFileData Type="Normal" Path="Common/circle.png" />
          </NodeObjectData>
          <NodeObjectData Name="normal" ActionTag="-1532763505" FrameEvent="" Tag="57" LeftMargin="104.0000" RightMargin="104.0000" TopMargin="677.8586" BottomMargin="346.1414" ctype="SpriteObjectData">
            <Position X="360.0000" Y="474.1414" />
            <Scale ScaleX="0.6000" ScaleY="0.6000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="512.0000" Y="256.0000" />
            <PrePosition X="0.5000" Y="0.3704" />
            <PreSize X="0.0000" Y="0.0000" />
            <Children>
              <NodeObjectData Name="normal_title" ActionTag="-863378685" FrameEvent="" Tag="58" LeftMargin="142.0000" RightMargin="142.0000" TopMargin="102.3565" BottomMargin="85.6435" ctype="SpriteObjectData">
                <Position X="256.0000" Y="119.6435" />
                <Scale ScaleX="1.4000" ScaleY="1.4000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="230.0000" Y="68.0000" />
                <PrePosition X="0.5000" Y="0.4674" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Scene/Level/normal.png" />
              </NodeObjectData>
            </Children>
            <FileData Type="Normal" Path="Common/title2.png" />
          </NodeObjectData>
          <NodeObjectData Name="limited" ActionTag="721578057" FrameEvent="" Tag="50" LeftMargin="104.0000" RightMargin="104.0000" TopMargin="846.5022" BottomMargin="177.4978" ctype="SpriteObjectData">
            <Position X="360.0000" Y="305.4978" />
            <Scale ScaleX="0.6000" ScaleY="0.6000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="512.0000" Y="256.0000" />
            <PrePosition X="0.5000" Y="0.2387" />
            <PreSize X="0.0000" Y="0.0000" />
            <Children>
              <NodeObjectData Name="limited_title" ActionTag="-1602070956" FrameEvent="" Tag="51" LeftMargin="142.0000" RightMargin="142.0000" TopMargin="102.3565" BottomMargin="85.6435" ctype="SpriteObjectData">
                <Position X="256.0000" Y="119.6435" />
                <Scale ScaleX="1.4000" ScaleY="1.4000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="228.0000" Y="68.0000" />
                <PrePosition X="0.5000" Y="0.4674" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Scene/Level/Limited.png" />
              </NodeObjectData>
            </Children>
            <FileData Type="Normal" Path="Common/title2.png" />
          </NodeObjectData>
        </Children>
      </ObjectData>
    </Content>
    <CameraPosition ValueX="0.0000" ValueY="5.0000" ValueZ="-1.0000" />
    <CameraRotation ValueX="0.0000" ValueY="0.0000" ValueZ="0.0000" />
  </Content>
</GameProjectFile>