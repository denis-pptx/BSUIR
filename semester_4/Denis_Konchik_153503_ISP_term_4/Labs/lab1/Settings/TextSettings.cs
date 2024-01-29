using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1.Settings
{
    public static class TextSettings
    {
        public const int OutputLabelDefaultFontSize = 20;
        public const int EntryLabelDefaultFontSize = 68;
        public const int MaxDigitsInEntryNumber = 16;

        public const int MaxEntryLabelUnscaledTextLength = 10;
        public const int MaxOutputLabelUnscaledTextLength = 25;
        public static int FontSizeByTextLength(LabelType labelType, int textLength)
        {
            int maxLabelUnscaledTextLength = labelType switch
            {
                LabelType.Entry => MaxEntryLabelUnscaledTextLength,
                LabelType.Output => MaxOutputLabelUnscaledTextLength,
                _ => 10
            };

            int unscaledFontSize = labelType switch
            {
                LabelType.Entry => EntryLabelDefaultFontSize,
                LabelType.Output => OutputLabelDefaultFontSize,
                _ => 10
            };

            if (textLength <= maxLabelUnscaledTextLength)
            {
                return unscaledFontSize;
            }
            else
            {
                //return (int)(unscaledFontSize * ((double)maxLabelUnscaledTextLength / textLength));
                return (int)(unscaledFontSize * ((double)maxLabelUnscaledTextLength / textLength));
            }
        }
    }
}
