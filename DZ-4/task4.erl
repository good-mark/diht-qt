-module(unylo).
%-compile(export_all).

getSize(Size1, Size2) ->
if 
Size1 < Size2 -> Size1;
true -> Size2 - Size2 rem 8
end.

getTrueChars(Text) ->
AllExceptLastByteSize = bit_size(Text) - 8,
<<All:AllExceptLastByteSize/bitstring, FirstBit:1/bitstring, SecondBit:1/bitstring, Rest:6/bitstring>> = Text,
%erlang:display(FirstBit),
%erlang:display(SecondBit),
case FirstBit of
<<0:1>> -> 
Sz = bit_size(Text),
{Text, Sz};
<<1:1>> ->
    case SecondBit of
    <<1:1>> -> {All, AllExceptLastByteSize};
    _ -> getTrueChars(All)
    end
end.


insert(Text, Pic, CurPos) ->
End = bit_size(Text),
%erlang:display(End),
%erlang:display(CurPos),
case CurPos of
End -> Pic;
_ -> 
<<_:CurPos/bitstring, Bitt:1/bitstring, _/bitstring>> = Text,
Om = CurPos * 8,
<<First:Om/bitstring, SevenMore:7/bitstring, _:1/bitstring, Last/bitstring>> = Pic,
CurPos2 = CurPos + 1,
Pic2 = <<First/bitstring, SevenMore:7/bitstring, Bitt/bitstring, Last/bitstring>>,
insert(Text, Pic2, CurPos2)
end.


getTrueSize(Pic, BitSize, 32) ->
<<Size:32/integer>> = BitSize,
{Size, Pic};
getTrueSize(Pic, BitSize, Step) ->
<<_:7/bitstring, Bitt:1/bitstring, Pic2/bitstring>> = Pic,
Step2 = Step + 1,
NewBitSize = <<BitSize/bitstring, Bitt/bitstring>>,
getTrueSize(Pic2, NewBitSize, Step2).


uninsert(Text, Pict, CurPos, Size) ->
%erlang:display(bit_size(Pict)),
%erlang:display(CurPos9),
%erlang:display(Size),
case CurPos of
Size -> Text;
_ ->
Om = CurPos*8,
<<_:Om/bitstring, SevenMore:7/bitstring, Bitt:1/bitstring, _/bitstring>> = Pict,
CurPos2 = CurPos + 1,
ResultText = <<Text/bitstring, Bitt/bitstring>>,
uninsert(ResultText, Pict, CurPos2, Size)
end.


main(_) ->
{_, Image} = file:read_file("testpic.bmp"),
<<_:144/bitstring, Width:32/little, Height:32/little, _/binary>> = Image,
Size = 3 * Width * Height,
Size1 = Size * 8, 
<<Before:432/bitstring, Pic:Size1/bitstring, After/binary>> = Image,


FreeSize = Size - 32,
{_, Text} = file:read_file("teststr.txt"),
SizeText = bit_size(Text),
TrueSize = getSize(SizeText, FreeSize),
erlang:display(SizeText),
erlang:display(FreeSize),
<<TrueText:TrueSize/bitstring, _/bitstring>> = Text,
{TrueTrueText, TrueTrueSize} =
case TrueSize of
SizeText -> {TrueText, TrueSize};
_ -> getTrueChars(TrueText)
end,
SizeForWrite = <<TrueTrueSize:32/integer>>,
TextForWrite = <<SizeForWrite/bitstring, TrueTrueText/bitstring>>,
erlang:display(bit_size(TextForWrite)),
erlang:display(TrueTrueSize),

InsertResult = insert(TextForWrite, Pic, 0),
erlang:display(asbbc),
erlang:display(bit_size(InsertResult)),
ResultPic = <<Before/bitstring, InsertResult/bitstring, After/bitstring>>,
file:write_file("resultpic.bmp", ResultPic),


{ok, MyPic} = file:read_file("resultpic.bmp"),
<<_:432/bitstring, PicPic:Size1/bitstring, _/binary>> = MyPic,
erlang:display(bit_size(PicPic)),
{ExtractedSize, CuttedPixels} = getTrueSize(PicPic, <<>>, 0),
erlang:display(ExtractedSize),
erlang:display(bit_size(CuttedPixels)),
ResultTextt = uninsert(<<>>, CuttedPixels, 0, ExtractedSize),
erlang:display(ExtractedSize),
file:write_file("resultstr.txt", ResultTextt).




