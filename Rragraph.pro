TARGET = Rragraph
TEMPLATE = app

HEADERS += \
    qwt-6.0.1/qwt_text_label.h \
    qwt-6.0.1/qwt_text_engine.h \
    qwt-6.0.1/qwt_text.h \
    qwt-6.0.1/qwt_symbol.h \
    qwt-6.0.1/qwt_spline.h \
    qwt-6.0.1/qwt_series_data.h \
    qwt-6.0.1/qwt_scale_widget.h \
    qwt-6.0.1/qwt_scale_map.h \
    qwt-6.0.1/qwt_scale_engine.h \
    qwt-6.0.1/qwt_scale_draw.h \
    qwt-6.0.1/qwt_scale_div.h \
    qwt-6.0.1/qwt_point_polar.h \
    qwt-6.0.1/qwt_point_3d.h \
    qwt-6.0.1/qwt_plot_zoomer.h \
    qwt-6.0.1/qwt_plot_seriesitem.h \
    qwt-6.0.1/qwt_plot_picker.h \
    qwt-6.0.1/qwt_plot_marker.h \
    qwt-6.0.1/qwt_plot_layout.h \
    qwt-6.0.1/qwt_plot_item.h \
    qwt-6.0.1/qwt_plot_grid.h \
    qwt-6.0.1/qwt_plot_dict.h \
    qwt-6.0.1/qwt_plot_curve.h \
    qwt-6.0.1/qwt_plot_canvas.h \
    qwt-6.0.1/qwt_plot.h \
    qwt-6.0.1/qwt_picker_machine.h \
    qwt-6.0.1/qwt_picker.h \
    qwt-6.0.1/qwt_panner.h \
    qwt-6.0.1/qwt_painter.h \
    qwt-6.0.1/qwt_null_paintdevice.h \
    qwt-6.0.1/qwt_math.h \
    qwt-6.0.1/qwt_legend_itemmanager.h \
    qwt-6.0.1/qwt_legend_item.h \
    qwt-6.0.1/qwt_legend.h \
    qwt-6.0.1/qwt_interval.h \
    qwt-6.0.1/qwt_global.h \
    qwt-6.0.1/qwt_event_pattern.h \
    qwt-6.0.1/qwt_dyngrid_layout.h \
    qwt-6.0.1/qwt_curve_fitter.h \
    qwt-6.0.1/qwt_color_map.h \
    qwt-6.0.1/qwt_clipper.h \
    qwt-6.0.1/qwt_abstract_scale_draw.h \
    Canvas/Canvas.h \
    Canvas/Properties/Properties.h \
    Canvas/Properties/AxesParameters.h \
    qwt-6.0.1/qwt_plot_renderer.h \
    Canvas/Data/Column.h \
    Canvas/Data/ReaderFile.h \
    Canvas/Model/Columns.h \
    Canvas/Model/DynamicColumn.h \
    Canvas/Curves/PlotCurve.h \
    Canvas/Model/ColumnsModel.h \
    Canvas/Data/DataFromFile.h \
    Canvas/Data/Data.h \
    Canvas/Properties/ColumnsProperties.h \
    Canvas/Properties/ColumnsDelegates/HeaderDelegate.h \
    Canvas/Properties/ColumnsDelegates/MultDelegate.h \
    Canvas/Properties/ColumnsDelegates/CurveStyleDelegate.h \
    Canvas/Properties/ColumnsDelegates/PainterListItem.h \
    MainWindow/MainWindow.h \
    Canvas/Properties/DataFromProject.h \
    Styles/Item/Item.h \
    Styles/Model/Model.h \
    Styles/View/StylesEditor.h \
    Styles/Model/Children/PlotStyleModel.h \
    Styles/Model/Children/CurveStyleModel.h \
    Styles/Delegate/Delegate.h \
    Styles/Delegate/Delegates/Delegates.h \
    Canvas/Data/FilePathParsing/FilePathParsing.h \
    Styles/StylesCurve.h \
    MainWindow/Guide/Guide.h \
    Styles/Delegate/TextDelegate.h \
    MainWindow/Translator/Translator.h \
    MainWindow/RecentlyClosed/RecentlyClosed.h \
    MainWindow/MdiArea/MdiArea.h
SOURCES += \
    qwt-6.0.1/qwt_text_label.cpp \
    qwt-6.0.1/qwt_text_engine.cpp \
    qwt-6.0.1/qwt_text.cpp \
    qwt-6.0.1/qwt_symbol.cpp \
    qwt-6.0.1/qwt_spline.cpp \
    qwt-6.0.1/qwt_series_data.cpp \
    qwt-6.0.1/qwt_scale_widget.cpp \
    qwt-6.0.1/qwt_scale_map.cpp \
    qwt-6.0.1/qwt_scale_engine.cpp \
    qwt-6.0.1/qwt_scale_draw.cpp \
    qwt-6.0.1/qwt_scale_div.cpp \
    qwt-6.0.1/qwt_point_polar.cpp \
    qwt-6.0.1/qwt_point_3d.cpp \
    qwt-6.0.1/qwt_plot_zoomer.cpp \
    qwt-6.0.1/qwt_plot_xml.cpp \
    qwt-6.0.1/qwt_plot_seriesitem.cpp \
    qwt-6.0.1/qwt_plot_picker.cpp \
    qwt-6.0.1/qwt_plot_marker.cpp \
    qwt-6.0.1/qwt_plot_layout.cpp \
    qwt-6.0.1/qwt_plot_item.cpp \
    qwt-6.0.1/qwt_plot_grid.cpp \
    qwt-6.0.1/qwt_plot_dict.cpp \
    qwt-6.0.1/qwt_plot_curve.cpp \
    qwt-6.0.1/qwt_plot_canvas.cpp \
    qwt-6.0.1/qwt_plot_axis.cpp \
    qwt-6.0.1/qwt_plot.cpp \
    qwt-6.0.1/qwt_picker_machine.cpp \
    qwt-6.0.1/qwt_picker.cpp \
    qwt-6.0.1/qwt_panner.cpp \
    qwt-6.0.1/qwt_painter.cpp \
    qwt-6.0.1/qwt_null_paintdevice.cpp \
    qwt-6.0.1/qwt_math.cpp \
    qwt-6.0.1/qwt_legend_item.cpp \
    qwt-6.0.1/qwt_legend.cpp \
    qwt-6.0.1/qwt_interval.cpp \
    qwt-6.0.1/qwt_event_pattern.cpp \
    qwt-6.0.1/qwt_dyngrid_layout.cpp \
    qwt-6.0.1/qwt_curve_fitter.cpp \
    qwt-6.0.1/qwt_color_map.cpp \
    qwt-6.0.1/qwt_clipper.cpp \
    qwt-6.0.1/qwt_abstract_scale_draw.cpp \
    main.cpp \
    Canvas/Canvas.cpp \
    Canvas/Properties/Properties.cpp \
    Canvas/Properties/AxesParameters.cpp \
    qwt-6.0.1/qwt_plot_renderer.cpp \
    Canvas/Data/Column.cpp \
    Canvas/Data/ReaderFile.cpp \
    Canvas/Model/Columns.cpp \
    Canvas/Curves/PlotCurve.cpp \
    Canvas/Model/ColumnsModel.cpp \
    Canvas/Data/DataFromFile.cpp \
    Canvas/Data/Data.cpp \
    Canvas/Properties/ColumnsProperties.cpp \
    Canvas/Properties/ColumnsDelegates/HeaderDelegate.cpp \
    Canvas/Properties/ColumnsDelegates/MultDelegate.cpp \
    Canvas/Properties/ColumnsDelegates/CurveStyleDelegate.cpp \
    Canvas/Properties/ColumnsDelegates/PainterListItem.cpp \
    MainWindow/MainWindow.cpp \
    Styles/Item/Item.cpp \
    Styles/Model/Model.cpp \
    Styles/View/StylesEditor.cpp \
    Styles/Model/Children/PlotStyleModel.cpp \
    Styles/Model/Children/CurveStyleModel.cpp \
    Styles/Delegate/Delegate.cpp \
    Styles/Delegate/Delegates/Int.cpp \
    Styles/Delegate/Delegates/Delegates.cpp \
    Styles/Delegate/Delegates/ComboBox.cpp \
    Styles/StyleReader.cpp \
    Canvas/Data/FilePathParsing/FilePathParsing.cpp \
    Styles/StylesCurve.cpp \
    MainWindow/Guide/Guide.cpp \
    Styles/Delegate/TextDelegate.cpp \
    MainWindow/Translator/Translator.cpp \
    MainWindow/RecentlyClosed/RecentlyClosed.cpp \
    MainWindow/MdiArea/TileMethodsMdiArea.cpp \
    MainWindow/MdiArea/SlotsMdiArea.cpp \
    MainWindow/MdiArea/PublicMethodsMdiArea.cpp \
    MainWindow/MdiArea/AuxiliaryMethodsMdiArea.cpp

RESOURCES += \
    resources.qrc

FORMS += \
    Canvas/Properties/Properties.ui \
    Canvas/Properties/AxesParameters.ui \
    Canvas/Properties/ColumnsProperties.ui \
    MainWindow/MainWindow.ui \
    Styles/View/StylesEditor.ui

TRANSLATIONS = translation_ru.ts

RC_FILE = icon.rc







































































