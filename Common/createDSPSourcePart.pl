#!/usr/bin/perl 

if($#ARGV < 0)
{
    print "Usage : $0 arg_file\n";
    exit;
}

$rel_path = "../../..";

@out_packages = ();
@out_h        = ();
@out_cpp      = ();
@out_inl      = ();
@out_y        = ();
@out_l        = ();
@out_def      = ();

$out_libname  = "";

for $i (0..$#ARGV)
{
    $_ = $ARGV[$i];

    if(m/\.def/)
    {
        push(@out_def, $_);
    }
    else
    {
        processPack($ARGV[$i]);
    }
}

#print "$#out_packages\r\n";
#print "$#out_h\r\n";
#print "$#out_cpp\r\n";
#print "$#out_inl\r\n";

printTargets();

exit;

sub processPack
{
    local $in_name = shift(@_);

    local @l_input  = ();
    local @l_in_h   = ();
    local @l_in_inl = ();
    local @l_in_cpp = ();
    local @l_in_l   = ();
    local @l_in_y   = ();

    open(IN, "cat $in_name |") || die "Could not open $in_name\r\n";

    while(<IN>)
    {
        push(@l_input, split(' ', $_));
    }
    
    close(IN);
   
    if($#l_input < 1)
    {
        print "Input to short\r\n";
        exit;
    }
    
          $out_libname = shift(@l_input);
    local $l_package   = shift(@l_input);
    local $l_basedir   = shift(@l_input)."/";
    
#    print "Package : $l_package\n";
#    print "Basedir : $l_basedir\n";
    
    for $entry (@l_input)
    {
        $_ = $entry;
        $_ =~ s/$l_basedir//;
        
        if(m/\.h/)
        {
            push(@l_in_h, $_);
        }
        elsif(m/\.cpp/)
        {
            push(@l_in_cpp, $_);
        }
        elsif(m/\.inl/)
        {
            push(@l_in_inl, $_);
        }
        elsif(m/\.l/)
        {
            push(@l_in_l, $_);
        }
        elsif(m/\.y/)
        {
            push(@l_in_y, $_);
        }
        else
        {
            print "Error unknown filetype $_\n";
        }
    }

    push(@out_packages, $l_package);
    push(@out_h,        [@l_in_h]);
    push(@out_cpp,      [@l_in_cpp]);
    push(@out_inl,      [@l_in_inl]);
    push(@out_l,        [@l_in_l]);
    push(@out_y,        [@l_in_y]);
}

sub printHeader
{
    local $pack = shift(@_);
    local $hdr  = shift(@_);
    local $ysrc = shift(@_);

    local $i;

    print "# Begin Group \"$pack h\"\r\n";
    print "# PROP Default_Filter \"\"\r\n";
    
    for $i (0..$#$hdr)
    {
        print "\r\n";
        print "# Begin Source File\r\n";
        print "SOURCE=$rel_path/$$hdr[$i]\r\n";

        $_ = $$hdr[$i];
        if(m/_qt\.h/)
        {
            $qtfile = $_;
            $qifile = $qtfile;
            $qifile =~ s/(.*\/)//g;
            $qifile =~ s/\.h/_moc\.cpp/;

            print "\r\n";
            print "!IF  \"\$(CFG)\" == \"${out_libname}Lib - Win32 Release\"\r\n";
            print "\r\n";
            print "!ELSEIF  \"\$(CFG)\" == \"${out_libname}Lib - Win32 Debug\"\r\n";
            print "\r\n";
            print "# Begin Custom Build\r\n";
            print "InputPath=../../../$qtfile\r\n";
            print "\r\n";
            print "BuildCmds= \\\r\n";
            print "\moc.exe ../../../$qtfile -i -o $qifile\r\n";
            print "\r\n";
            print "\"$qifile\" : \$(SOURCE) \"\$(INTDIR)\" \"\$(OUTDIR)\"\r\n";
            print "   \$(BuildCmds)\r\n";
            print "\r\n";
            print "# End Custom Build\r\n";
            print "\r\n";
            print "!ENDIF\r\n";
            print "\r\n";
        }

        print "# End Source File\r\n";
        print "\r\n";
    }

    for $i (0..$#$ysrc)
    {
        $yfile = $$ysrc[$i];

        $hfile = $yfile;
        $hfile =~ s/(.*\/)//g;
        $hfile =~ s/\.y/\.tab.h/;

        print "\r\n";
        print "# Begin Source File\r\n";
        print "SOURCE=$hfile\r\n";
        print "# End Source File\r\n";
        print "\r\n";
    }
    
    print "# End Group\r\n";
}

sub printInline
{
    local $pack = shift(@_);
    local $inl  = shift(@_);
    local $i;

    print "# Begin Group \"$pack inl\"\r\n";
    print "# PROP Default_Filter \"\"\r\n";
    
    for $i (0..$#$inl)
    {
        print "\r\n";
        print "# Begin Source File\r\n";
        print "SOURCE=$rel_path/$$inl[$i]\r\n";
        print "# End Source File\r\n";
        print "\r\n";
    }
    
    print "# End Group\r\n";
}

sub printSource
{
    local $pack = shift(@_);
    local $src  = shift(@_);
    local $ysrc = shift(@_);
    local $lsrc = shift(@_);
    local $i;

    print "# Begin Group \"$pack cpp\"\r\n";
    print "# PROP Default_Filter \"\"\r\n";
    
    for $i (0..$#$src)
    {
        print "\r\n";
        print "# Begin Source File\r\n";
        print "SOURCE=$rel_path/$$src[$i]\r\n";
        print "# End Source File\r\n";
        print "\r\n";
    }
    
    for $i (0..$#$ysrc)
    {
        $yfile = $$ysrc[$i];

        $cfile = $yfile;
        $cfile =~ s/(.*\/)//g;
        $cfile =~ s/\.y/\.tab.cpp/;

        print "\r\n";
        print "# Begin Source File\r\n";
        print "SOURCE=$cfile\r\n";
        print "# End Source File\r\n";
        print "\r\n";
    }

    for $i (0..$#$lsrc)
    {
        $lfile = $$lsrc[$i];

        $cfile = $lfile;
        $cfile =~ s/(.*\/)//g;
        $cfile =~ s/\.l/\.lex.cpp/;

        print "\r\n";
        print "# Begin Source File\r\n";
        print "SOURCE=$cfile\r\n";
        print "# End Source File\r\n";
        print "\r\n";
    }

    print "# End Group\r\n";
}

sub printScanParse
{
    local $pack = shift(@_);
    local $ysrc = shift(@_);
    local $lsrc = shift(@_);
    local $i;

    print "# Begin Group \"$pack ly\"\r\n";
    print "# PROP Default_Filter \"\"\r\n";
    
    for $i (0..$#$ysrc)
    {
        $yfile = $$ysrc[$i];
        $yfp   = $yfile;

        $yfile =~ s/(.*\/)//g;

        $fbase = $yfile;
        $fbase =~ s/\.y//;

        print "\r\n";
        print "# Begin Source File\r\n";
        print "SOURCE=../../../$yfp\r\n";
        print "\r\n";
        print "!IF  \"\$(CFG)\" == \"${out_libname}Lib - Win32 Release\"\r\n";
        print "\r\n";
        print "!ELSEIF  \"\$(CFG)\" == \"${out_libname}Lib - Win32 Debug\"\r\n";
        print "\r\n";
        print "# Begin Custom Build\r\n";
        print "InputPath=../../../$yfp\r\n";
        print "\r\n";
        print "BuildCmds= \\\r\n";
        print "\tbison.exe -d -v -p${fbase}_  -b${fbase}_ ../../../$yfp \\\r\n";
        print "\tmove ${fbase}_.tab.c ${fbase}.tab.cpp \\\r\n";
        print "\tmove ${fbase}_.tab.h ${fbase}.tab.h \\\r\n";
        print "\tmove ${fbase}_.output ${fbase}.tab.output \\\r\n";
        print "\r\n";
        print "\"$fbase.tab.cpp\" : \$(SOURCE) \"\$(INTDIR)\" \"\$(OUTDIR)\"\r\n";
        print "   \$(BuildCmds)\r\n";
        print "\r\n";
        print "\"$fbase.tab.h\" : \$(SOURCE) \"\$(INTDIR)\" \"\$(OUTDIR)\"\r\n";
        print "   \$(BuildCmds)\r\n";
        print "# End Custom Build\r\n";
        print "\r\n";
        print "!ENDIF\r\n";
        print "\r\n";
        print "# End Source File\r\n";
        print "\r\n";
    }

    for $i (0..$#$lsrc)
    {
        $lfile = $$lsrc[$i];

        $cfile = $lfile;
        $cfile =~ s/(.*\/)//g;

        $fbase = $lfile;
        $fbase =~ s/(.*\/)//g;
        $fbase =~ s/\.l//;

        print "\r\n";
        print "# Begin Source File\r\n";
        print "SOURCE=../../../$lfile\r\n";
        print "\r\n";
        print "!IF  \"\$(CFG)\" == \"${out_libname}Lib - Win32 Release\"\r\n";
        print "\r\n";
        print "!ELSEIF  \"\$(CFG)\" == \"${out_libname}Lib - Win32 Debug\"\r\n";
        print "\r\n";
        print "# Begin Custom Build\r\n";
        print "InputPath=../../../$lfile\r\n";
        print "\r\n";
        print "BuildCmds= \\\r\n";
        print "\tflex.exe -l -P${fbase}_ ../../../$lfile \\\r\n";
        print "\tmove lex.${fbase}_.c ${fbase}.lex.cpp \\\r\n";
        print "\r\n";
        print "\"$fbase.lex.cpp\" : \$(SOURCE) \"\$(INTDIR)\" \"\$(OUTDIR)\"\r\n";
        print "   \$(BuildCmds)\r\n";
        print "\r\n";
        print "# End Custom Build\r\n";
        print "\r\n";
        print "!ENDIF\r\n";
        print "\r\n";
        print "# End Source File\r\n";
        print "\r\n";
    }

    print "# End Group\r\n";
}

sub printResourse
{
    local $files = shift(@_);

    for $i (0..$#$files)
    {
        print "\r\n";
        print "# Begin Source File\r\n";
        print "SOURCE=$$files[$i]\r\n";
        print "# End Source File\r\n";
        print "\r\n";
    }
}

sub printTargets
{
    local $i;

    print "# Begin Target\r\n";
    print "\r\n";
    print "# Name \"${out_libname}Lib - Win32 Release\"\r\n";
    print "# Name \"${out_libname}Lib - Win32 Debug\"\r\n";
    print "\r\n";

    print "# Begin Group \"Header Files\"\r\n";
    print "# PROP Default_Filter \"h;hpp;hxx;hm\"\r\n";
    print "\r\n";
    for $i (0..$#out_packages)
    {
        printHeader($out_packages[$i], $out_h[$i], $out_y[$i]);
    }
    print "\r\n";
    print "# End Group\r\n";

    print "\r\n";
    print "\r\n";

    print "# Begin Group \"Inline Files\"\r\n";
    print "# PROP Default_Filter \"inl\"\r\n";
    print "\r\n";
    for $i (0..$#out_packages)
    {
        printInline($out_packages[$i], $out_inl[$i]);
    }
    print "\r\n";
    print "# End Group\r\n";

    print "\r\n";
    print "\r\n";

    print "# Begin Group \"Source Files\"\r\n";
    print "# PROP Default_Filter \"cpp;c;cxx;rc;def;r;odl;idl;hpj;bat\"\r\n";
    print "\r\n";
    for $i (0..$#out_packages)
    {
        printSource($out_packages[$i], $out_cpp[$i], $out_y[$i], $out_l[$i]);
    }
    print "\r\n";
    print "# End Group\r\n";

    print "# Begin Group \"Scan/Parse Files\"\r\n";
    print "# PROP Default_Filter \"y;l\"\r\n";
    print "\r\n";
    for $i (0..$#out_packages)
    {
        printScanParse($out_packages[$i], $out_y[$i], $out_l[$i]);
    }
    print "\r\n";
    print "# End Group\r\n";

    print "# Begin Group \"Resource Files\"\r\n";
    print "# PROP Default_Filter \"ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe\"\r\n";
    print "\r\n";
    
    printResourse([@out_def]);

    print "\r\n";
    print "# End Group\r\n";

    print "\r\n";
    print "# End Target\r\n";
    print "# End Project\r\n";
}


sub xxx
{
        }
