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

#print "$#out_packages\n";
#print "$#out_h\n";
#print "$#out_cpp\n";
#print "$#out_inl\n";

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

    open(IN, "cat $in_name |") || die "Could not open $in_name\n";

    while(<IN>)
    {
        push(@l_input, split(' ', $_));
    }
    
    close(IN);
   
    if($#l_input < 1)
    {
        print "Input to short\n";
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

    print "# Begin Group \"$pack h\"\n";
    print "# PROP Default_Filter \"\"\n";
    
    for $i (0..$#$hdr)
    {
        print "\n";
        print "# Begin Source File\n";
        print "SOURCE=$rel_path/$$hdr[$i]\n";

        $_ = $$hdr[$i];
        if(m/_qt\.h/)
        {
            $qtfile = $_;
            $qifile = $qtfile;
            $qifile =~ s/(.*\/)//g;
            $qifile =~ s/\.h/_moc\.cpp/;

            print "\n";
            print "!IF  \"\$(CFG)\" == \"${out_libname}Lib - Win32 Release\"\n";
            print "\n";
            print "!ELSEIF  \"\$(CFG)\" == \"${out_libname}Lib - Win32 Debug\"\n";
            print "\n";
            print "# Begin Custom Build\n";
            print "InputPath=../../../$qtfile\n";
            print "\n";
            print "BuildCmds= \\\n";
            print "\moc.exe ../../../$qtfile -i -o $qifile\n";
            print "\n";
            print "\"$qifile\" : \$(SOURCE) \"\$(INTDIR)\" \"\$(OUTDIR)\"\n";
            print "   \$(BuildCmds)\n";
            print "\n";
            print "# End Custom Build\n";
            print "\n";
            print "!ENDIF\n";
            print "\n";
        }

        print "# End Source File\n";
        print "\n";
    }

    for $i (0..$#$ysrc)
    {
        $yfile = $$ysrc[$i];

        $hfile = $yfile;
        $hfile =~ s/(.*\/)//g;
        $hfile =~ s/\.y/\.tab.h/;

        print "\n";
        print "# Begin Source File\n";
        print "SOURCE=$hfile\n";
        print "# End Source File\n";
        print "\n";
    }
    
    print "# End Group\n";
}

sub printInline
{
    local $pack = shift(@_);
    local $inl  = shift(@_);
    local $i;

    print "# Begin Group \"$pack inl\"\n";
    print "# PROP Default_Filter \"\"\n";
    
    for $i (0..$#$inl)
    {
        print "\n";
        print "# Begin Source File\n";
        print "SOURCE=$rel_path/$$inl[$i]\n";
        print "# End Source File\n";
        print "\n";
    }
    
    print "# End Group\n";
}

sub printSource
{
    local $pack = shift(@_);
    local $src  = shift(@_);
    local $ysrc = shift(@_);
    local $lsrc = shift(@_);
    local $i;

    print "# Begin Group \"$pack cpp\"\n";
    print "# PROP Default_Filter \"\"\n";
    
    for $i (0..$#$src)
    {
        print "\n";
        print "# Begin Source File\n";
        print "SOURCE=$rel_path/$$src[$i]\n";
        print "# End Source File\n";
        print "\n";
    }
    
    for $i (0..$#$ysrc)
    {
        $yfile = $$ysrc[$i];

        $cfile = $yfile;
        $cfile =~ s/(.*\/)//g;
        $cfile =~ s/\.y/\.tab.cpp/;

        print "\n";
        print "# Begin Source File\n";
        print "SOURCE=$cfile\n";
        print "# End Source File\n";
        print "\n";
    }

    for $i (0..$#$lsrc)
    {
        $lfile = $$lsrc[$i];

        $cfile = $lfile;
        $cfile =~ s/(.*\/)//g;
        $cfile =~ s/\.l/\.lex.cpp/;

        print "\n";
        print "# Begin Source File\n";
        print "SOURCE=$cfile\n";
        print "# End Source File\n";
        print "\n";
    }

    print "# End Group\n";
}

sub printScanParse
{
    local $pack = shift(@_);
    local $ysrc = shift(@_);
    local $lsrc = shift(@_);
    local $i;

    print "# Begin Group \"$pack ly\"\n";
    print "# PROP Default_Filter \"\"\n";
    
    for $i (0..$#$ysrc)
    {
        $yfile = $$ysrc[$i];
        $yfp   = $yfile;

        $yfile =~ s/(.*\/)//g;

        $fbase = $yfile;
        $fbase =~ s/\.y//;

        print "\n";
        print "# Begin Source File\n";
        print "SOURCE=../../../$yfp\n";
        print "\n";
        print "!IF  \"\$(CFG)\" == \"${out_libname}Lib - Win32 Release\"\n";
        print "\n";
        print "!ELSEIF  \"\$(CFG)\" == \"${out_libname}Lib - Win32 Debug\"\n";
        print "\n";
        print "# Begin Custom Build\n";
        print "InputPath=../../../$yfp\n";
        print "\n";
        print "BuildCmds= \\\n";
        print "\tbison.exe -d -v -p${fbase}_  -b${fbase}_ ../../../$yfp \\\n";
        print "\tmove ${fbase}_.tab.c ${fbase}.tab.cpp \\\n";
        print "\tmove ${fbase}_.tab.h ${fbase}.tab.h \\\n";
        print "\tmove ${fbase}_.output ${fbase}.tab.output \\\n";
        print "\n";
        print "\"$fbase.tab.cpp\" : \$(SOURCE) \"\$(INTDIR)\" \"\$(OUTDIR)\"\n";
        print "   \$(BuildCmds)\n";
        print "\n";
        print "\"$fbase.tab.h\" : \$(SOURCE) \"\$(INTDIR)\" \"\$(OUTDIR)\"\n";
        print "   \$(BuildCmds)\n";
        print "# End Custom Build\n";
        print "\n";
        print "!ENDIF\n";
        print "\n";
        print "# End Source File\n";
        print "\n";
    }

    for $i (0..$#$lsrc)
    {
        $lfile = $$lsrc[$i];

        $cfile = $lfile;
        $cfile =~ s/(.*\/)//g;

        $fbase = $lfile;
        $fbase =~ s/(.*\/)//g;
        $fbase =~ s/\.l//;

        print "\n";
        print "# Begin Source File\n";
        print "SOURCE=../../../$lfile\n";
        print "\n";
        print "!IF  \"\$(CFG)\" == \"${out_libname}Lib - Win32 Release\"\n";
        print "\n";
        print "!ELSEIF  \"\$(CFG)\" == \"${out_libname}Lib - Win32 Debug\"\n";
        print "\n";
        print "# Begin Custom Build\n";
        print "InputPath=../../../$lfile\n";
        print "\n";
        print "BuildCmds= \\\n";
        print "\tflex.exe -l -P${fbase}_ ../../../$lfile \\\n";
        print "\tmove lex.${fbase}_.c ${fbase}.lex.cpp \\\n";
        print "\n";
        print "\"$fbase.lex.cpp\" : \$(SOURCE) \"\$(INTDIR)\" \"\$(OUTDIR)\"\n";
        print "   \$(BuildCmds)\n";
        print "\n";
        print "# End Custom Build\n";
        print "\n";
        print "!ENDIF\n";
        print "\n";
        print "# End Source File\n";
        print "\n";
    }

    print "# End Group\n";
}

sub printResourse
{
    local $files = shift(@_);

    for $i (0..$#$files)
    {
        print "\n";
        print "# Begin Source File\n";
        print "SOURCE=$$files[$i]\n";
        print "# End Source File\n";
        print "\n";
    }
}

sub printTargets
{
    local $i;

    print "# Begin Target\n";
    print "\n";
    print "# Name \"${out_libname}Lib - Win32 Release\"\n";
    print "# Name \"${out_libname}Lib - Win32 Debug\"\n";
    print "\n";

    print "# Begin Group \"Header Files\"\n";
    print "# PROP Default_Filter \"h;hpp;hxx;hm\"\n";
    print "\n";
    for $i (0..$#out_packages)
    {
        printHeader($out_packages[$i], $out_h[$i], $out_y[$i]);
    }
    print "\n";
    print "# End Group\n";

    print "\n";
    print "\n";

    print "# Begin Group \"Inline Files\"\n";
    print "# PROP Default_Filter \"inl\"\n";
    print "\n";
    for $i (0..$#out_packages)
    {
        printInline($out_packages[$i], $out_inl[$i]);
    }
    print "\n";
    print "# End Group\n";

    print "\n";
    print "\n";

    print "# Begin Group \"Source Files\"\n";
    print "# PROP Default_Filter \"cpp;c;cxx;rc;def;r;odl;idl;hpj;bat\"\n";
    print "\n";
    for $i (0..$#out_packages)
    {
        printSource($out_packages[$i], $out_cpp[$i], $out_y[$i], $out_l[$i]);
    }
    print "\n";
    print "# End Group\n";

    print "# Begin Group \"Scan/Parse Files\"\n";
    print "# PROP Default_Filter \"y;l\"\n";
    print "\n";
    for $i (0..$#out_packages)
    {
        printScanParse($out_packages[$i], $out_y[$i], $out_l[$i]);
    }
    print "\n";
    print "# End Group\n";

    print "# Begin Group \"Resource Files\"\n";
    print "# PROP Default_Filter \"ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe\"\n";
    print "\n";
    
    printResourse([@out_def]);

    print "\n";
    print "# End Group\n";

    print "\n";
    print "# End Target\n";
    print "# End Project\n";
}


sub xxx
{
        }
