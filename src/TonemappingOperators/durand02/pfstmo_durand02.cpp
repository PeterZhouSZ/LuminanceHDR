/**
 * @file pfstmo_durand02.cpp
 * @brief Tone map XYZ channels using Durand02 model
 *
 * Fast Bilateral Filtering for the Display of High-Dynamic-Range Images.
 * F. Durand and J. Dorsey.
 * In ACM Transactions on Graphics, 2002.
 *
 * 
 * This file is a part of Luminance package, based on pfstmo.
 * ---------------------------------------------------------------------- 
 * Copyright (C) 2003,2004 Grzegorz Krawczyk
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * ---------------------------------------------------------------------- 
 * 
 * @author Grzegorz Krawczyk, <krawczyk@mpi-sb.mpg.de>
 *
 * $Id: pfstmo_durand02.cpp,v 1.5 2009/02/23 19:09:41 rafm Exp $
 */

#include <math.h>
#include "Libpfs/pfs.h"
#include "tmo_durand02.h"

#include <iostream>

void pfstmo_durand02(pfs::Frame* frame, float sigma_s, float sigma_r, float baseContrast, ProgressHelper *ph)
{
    pfs::DOMIO pfsio;

    //--- default tone mapping parameters;
    //#ifdef HAVE_FFTW3F
    //  float sigma_s = 40.0f;
    //#else
    //float sigma_s = 8.0f;
    //#endif
    //float sigma_r = 0.4f;
    //float baseContrast = 5.0f;
    int downsample=1;
    bool original_algorithm = false;

    std::cout << "pfstmo_durand02" << std::endl;
    #ifdef HAVE_FFTW3F
      std::cout << "using fftw3f" << std::endl;
    #endif
    std::cout << "sigma_s: " << sigma_s << std::endl;
    std::cout << "sigma_r: " << sigma_r << std::endl;
    std::cout << "base contrast: " << baseContrast << std::endl;

    pfs::Channel *X, *Y, *Z;

    frame->getXYZChannels( X, Y, Z );
    frame->getTags()->setString("LUMINANCE", "RELATIVE");
    //---

    if( Y==NULL || X==NULL || Z==NULL)
      throw pfs::Exception( "Missing X, Y, Z channels in the PFS stream" );
        
    // tone mapping
    int w = Y->getCols();
    int h = Y->getRows();

    pfs::transformColorSpace( pfs::CS_XYZ, X, Y, Z, pfs::CS_RGB, X, Y, Z );
    tmo_durand02( w, h, X->getRawData(), Y->getRawData(), Z->getRawData(), sigma_s, sigma_r, baseContrast, downsample, !original_algorithm, ph );
    pfs::transformColorSpace( pfs::CS_RGB, X, Y, Z, pfs::CS_XYZ, X, Y, Z );
}

