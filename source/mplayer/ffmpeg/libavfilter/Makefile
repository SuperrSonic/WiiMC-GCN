include $(SUBDIR)../config.mak

NAME = avfilter
FFLIBS = avutil swscale
FFLIBS-$(CONFIG_ASYNCTS_FILTER) += avresample
FFLIBS-$(CONFIG_RESAMPLE_FILTER) += avresample

FFLIBS-$(CONFIG_ACONVERT_FILTER)             += swresample
FFLIBS-$(CONFIG_AMOVIE_FILTER)               += avformat avcodec
FFLIBS-$(CONFIG_ARESAMPLE_FILTER)            += swresample
FFLIBS-$(CONFIG_MOVIE_FILTER)                += avformat avcodec
FFLIBS-$(CONFIG_PAN_FILTER)                  += swresample
FFLIBS-$(CONFIG_REMOVELOGO_FILTER)           += avformat avcodec
FFLIBS-$(CONFIG_MP_FILTER)                   += avcodec postproc

HEADERS = asrc_abuffer.h                                                \
          avcodec.h                                                     \
          avfilter.h                                                    \
          avfiltergraph.h                                               \
          buffersink.h                                                  \
          buffersrc.h                                                   \
          version.h                                                     \
          vsrc_buffer.h                                                 \

OBJS = allfilters.o                                                     \
       audio.o                                                          \
       avfilter.o                                                       \
       avfiltergraph.o                                                  \
       buffer.o                                                         \
       buffersink.o                                                     \
       buffersrc.o                                                      \
       defaults.o                                                       \
       drawutils.o                                                      \
       formats.o                                                        \
       graphdump.o                                                      \
       graphparser.o                                                    \
       src_buffer.o                                                     \
       transform.o                                                      \
       vf_scale.o                                                       \
       video.o                                                          \


OBJS-$(CONFIG_AVCODEC)                       += avcodec.o
OBJS-$(CONFIG_AVFORMAT)                      += lavfutils.o
OBJS-$(CONFIG_SWSCALE)                       += lswsutils.o

OBJS-$(CONFIG_ACONVERT_FILTER)               += af_aconvert.o
OBJS-$(CONFIG_AFORMAT_FILTER)                += af_aformat.o
OBJS-$(CONFIG_AMERGE_FILTER)                 += af_amerge.o
OBJS-$(CONFIG_AMIX_FILTER)                   += af_amix.o
OBJS-$(CONFIG_ANULL_FILTER)                  += af_anull.o
OBJS-$(CONFIG_ARESAMPLE_FILTER)              += af_aresample.o
OBJS-$(CONFIG_ASHOWINFO_FILTER)              += af_ashowinfo.o
OBJS-$(CONFIG_ASPLIT_FILTER)                 += split.o
OBJS-$(CONFIG_ASTREAMSYNC_FILTER)            += af_astreamsync.o
OBJS-$(CONFIG_ASYNCTS_FILTER)                += af_asyncts.o
OBJS-$(CONFIG_EARWAX_FILTER)                 += af_earwax.o
OBJS-$(CONFIG_PAN_FILTER)                    += af_pan.o
OBJS-$(CONFIG_RESAMPLE_FILTER)               += af_resample.o
OBJS-$(CONFIG_SILENCEDETECT_FILTER)          += af_silencedetect.o
OBJS-$(CONFIG_VOLUME_FILTER)                 += af_volume.o

OBJS-$(CONFIG_AEVALSRC_FILTER)               += asrc_aevalsrc.o
OBJS-$(CONFIG_AMOVIE_FILTER)                 += src_movie.o
OBJS-$(CONFIG_ANULLSRC_FILTER)               += asrc_anullsrc.o

OBJS-$(CONFIG_ABUFFERSINK_FILTER)            += sink_buffer.o
OBJS-$(CONFIG_ANULLSINK_FILTER)              += asink_anullsink.o





OBJS-$(CONFIG_CELLAUTO_FILTER)               += vsrc_cellauto.o
OBJS-$(CONFIG_COLOR_FILTER)                  += vsrc_color.o
OBJS-$(CONFIG_FREI0R_SRC_FILTER)             += vf_frei0r.o
OBJS-$(CONFIG_LIFE_FILTER)                   += vsrc_life.o
OBJS-$(CONFIG_MANDELBROT_FILTER)             += vsrc_mandelbrot.o
OBJS-$(CONFIG_MOVIE_FILTER)                  += src_movie.o
OBJS-$(CONFIG_MPTESTSRC_FILTER)              += vsrc_mptestsrc.o
OBJS-$(CONFIG_NULLSRC_FILTER)                += vsrc_testsrc.o
OBJS-$(CONFIG_RGBTESTSRC_FILTER)             += vsrc_testsrc.o
OBJS-$(CONFIG_TESTSRC_FILTER)                += vsrc_testsrc.o

OBJS-$(CONFIG_BUFFERSINK_FILTER)             += sink_buffer.o
OBJS-$(CONFIG_NULLSINK_FILTER)               += vsink_nullsink.o



TESTPROGS = drawutils formats

TOOLS = graph2dot                                                       \
        lavfi-showfiltfmts                                              \
