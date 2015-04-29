<GameProjectFile>
  <PropertyGroup Type="Node" Name="ScoreAndLive" ID="61d1b659-75c3-4628-ae73-34a55d291e73" Version="2.2.1.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Node" FrameEvent="" Tag="5" ctype="SingleNodeObjectData">
        <Position X="0.0000" Y="0.0000" />
        <Scale ScaleX="1.0000" ScaleY="1.0000" />
        <AnchorPoint />
        <CColor A="255" R="255" G="255" B="255" />
        <Size X="0.0000" Y="0.0000" />
        <PrePosition X="0.0000" Y="0.0000" />
        <PreSize X="0.0000" Y="0.0000" />
        <Children>
          <NodeObjectData Name="bg" ActionTag="1297466392" FrameEvent="" Tag="1" RightMargin="-682.0000" BottomMargin="-86.0000" Scale9Enable="True" LeftEage="217" RightEage="188" TopEage="3" BottomEage="10" Scale9OriginX="217" Scale9OriginY="3" Scale9Width="277" Scale9Height="73" ctype="ImageViewObjectData">
            <Position X="0.0000" Y="0.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="682.0000" Y="86.0000" />
            <PrePosition X="0.0000" Y="0.0000" />
            <PreSize X="0.0000" Y="0.0000" />
            <Children>
              <NodeObjectData Name="lives" ActionTag="-1248027632" FrameEvent="" Tag="2" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" LeftMargin="-14.0004" RightMargin="568.0004" TopMargin="-19.6663" BottomMargin="-22.3337" ctype="SpriteObjectData">
                <Position X="49.9996" Y="41.6663" />
                <Scale ScaleX="0.5000" ScaleY="0.5000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="128.0000" Y="128.0000" />
                <PrePosition X="0.0733" Y="0.4845" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Scene/Game/lives.png" />
              </NodeObjectData>
              <NodeObjectData Name="prop_1" ActionTag="-2124103691" FrameEvent="" Tag="6" LeftMargin="1.6636" RightMargin="595.3364" TopMargin="108.5046" BottomMargin="-107.5046" ctype="SpriteObjectData">
                <Position X="1.6636" Y="-65.0046" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="85.0000" Y="85.0000" />
                <PrePosition X="0.0024" Y="-0.7559" />
                <PreSize X="0.0000" Y="0.0000" />
                <Children>
                  <NodeObjectData Name="fan" ActionTag="-955836042" FrameEvent="" Tag="2" LeftMargin="0.3571" RightMargin="-0.3571" TopMargin="3.7475" BottomMargin="-3.7475" ctype="SpriteObjectData">
                    <Position X="42.8571" Y="38.7525" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="85.0000" Y="85.0000" />
                    <PrePosition X="0.5042" Y="0.4559" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="Common/fan.png" />
                  </NodeObjectData>
                </Children>
                <FileData Type="Normal" Path="Scene/Game/prop.png" />
              </NodeObjectData>
              <NodeObjectData Name="prop_2" ActionTag="665040111" FrameEvent="" Tag="7" LeftMargin="1.6636" RightMargin="595.3364" TopMargin="208.7018" BottomMargin="-207.7018" ctype="SpriteObjectData">
                <Position X="1.6636" Y="-165.2018" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="85.0000" Y="85.0000" />
                <PrePosition X="0.0024" Y="-1.9210" />
                <PreSize X="0.0000" Y="0.0000" />
                <Children>
                  <NodeObjectData Name="Clock" ActionTag="179504293" FrameEvent="" Tag="2" LeftMargin="3.4286" RightMargin="5.5714" TopMargin="5.5714" BottomMargin="3.4286" ctype="SpriteObjectData">
                    <Position X="41.4286" Y="41.4286" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <Size X="76.0000" Y="76.0000" />
                    <PrePosition X="0.4874" Y="0.4874" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="Common/clock.png" />
                  </NodeObjectData>
                </Children>
                <FileData Type="Normal" Path="Scene/Game/prop.png" />
              </NodeObjectData>
            </Children>
            <FileData Type="Normal" Path="Scene/Game/title.png" />
          </NodeObjectData>
          <NodeObjectData Name="Label_live" ActionTag="-2056175832" FrameEvent="" Tag="52" LeftMargin="79.9999" RightMargin="-151.9999" TopMargin="40.2200" BottomMargin="-88.2200" FontSize="48" LabelText="X 5" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ctype="TextObjectData">
            <Position X="115.9999" Y="-64.2200" />
            <Scale ScaleX="0.7222" ScaleY="0.6465" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="64" G="39" B="7" />
            <Size X="72.0000" Y="48.0000" />
            <PrePosition X="0.0000" Y="0.0000" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="Font/Japan.ttc" />
          </NodeObjectData>
          <NodeObjectData Name="Label_Fan" ActionTag="393337429" FrameEvent="" Tag="53" LeftMargin="100.0000" RightMargin="-148.0000" TopMargin="165.0000" BottomMargin="-198.0000" FontSize="32" LabelText="X 1" ctype="TextObjectData">
            <Position X="100.0000" Y="-181.5000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleY="0.5000" />
            <CColor A="255" R="64" G="39" B="7" />
            <Size X="48.0000" Y="33.0000" />
            <PrePosition X="0.0000" Y="0.0000" />
            <PreSize X="0.0000" Y="0.0000" />
          </NodeObjectData>
          <NodeObjectData Name="Label_Clock" ActionTag="1377901369" FrameEvent="" Tag="54" LeftMargin="100.0000" RightMargin="-148.0000" TopMargin="250.5000" BottomMargin="-283.5000" FontSize="32" LabelText="X 1" ctype="TextObjectData">
            <Position X="100.0000" Y="-267.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleY="0.5000" />
            <CColor A="255" R="64" G="39" B="7" />
            <Size X="48.0000" Y="33.0000" />
            <PrePosition X="0.0000" Y="0.0000" />
            <PreSize X="0.0000" Y="0.0000" />
          </NodeObjectData>
          <NodeObjectData Name="Label_Score" ActionTag="898700548" FrameEvent="" Tag="55" LeftMargin="340.1693" RightMargin="-379.1693" TopMargin="5.2451" BottomMargin="-73.2451" FontSize="68" LabelText="0" ctype="TextObjectData">
            <Position X="359.6693" Y="-39.2451" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="64" G="36" B="7" />
            <Size X="39.0000" Y="68.0000" />
            <PrePosition X="0.0000" Y="0.0000" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="Font/Casper.ttf" />
          </NodeObjectData>
          <NodeObjectData Name="tools" ActionTag="2122110770" FrameEvent="" Tag="3" LeftMargin="574.0000" RightMargin="-702.0000" TopMargin="-20.3750" BottomMargin="-107.6250" TouchEnable="True" FontSize="14" ButtonText="" Scale9Enable="True" Scale9Width="128" Scale9Height="128" ctype="ButtonObjectData">
            <Position X="638.0000" Y="-43.6250" />
            <Scale ScaleX="0.6000" ScaleY="0.6000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="128.0000" Y="128.0000" />
            <PrePosition X="0.0000" Y="0.0000" />
            <PreSize X="0.0000" Y="0.0000" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" />
            <PressedFileData Type="Normal" Path="Common/tools_s.png" />
            <NormalFileData Type="Normal" Path="Common/tools.png" />
          </NodeObjectData>
        </Children>
      </ObjectData>
    </Content>
    <CameraPosition ValueX="0.0000" ValueY="5.0000" ValueZ="-1.0000" />
    <CameraRotation ValueX="0.0000" ValueY="0.0000" ValueZ="0.0000" />
  </Content>
</GameProjectFile>