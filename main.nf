#!/usr/bin/env nextflow

//params.fasta = "${baseDir}/data/test.fa"
//params.fasta = "${baseDir}/results/alignments/*.dpa_1000.*.tree.aln"
params.fasta = "/users/cn/efloden/projects/dpa-benchfam-100k/results/alignments/*.dpa_1000.*.tree.aln"
params.gaps = "${baseDir}/results/benchfam/gap/PF00005.dpa_1000.CLUSTALO.with.MAFFT_PARTTREE.tree_F2G.gap"

params.fa2gap = false

params.output = "${baseDir}/results/benchfam"


log.info """\
         R E G R E S S I V E   M S A   A n a l y s i s  ~  version 0.1"
         ======================================="
         Input Alignments (FA)                          : ${params.fasta}
         Input Alignments (GAPS)                        : ${params.gaps}   
         FA -->> GAP                                    : ${params.fa2gap}  
         Output directory (DIRECTORY)                   : ${params.output}
         \
         """
         .stripIndent()


// Channels containing sequences
if ( params.fasta ) {
  Channel
  .fromPath(params.fasta)
  .map { item -> [ item.baseName, item] }
  .set { faCh }
}

if ( params.gaps ) {
  Channel
  .fromPath(params.gaps)
  .map { item -> [ item.baseName, item] }
  .set { gapCh }
}

process fasta2Gap {
    tag "${id}"
    publishDir "${params.output}/gap", mode: 'copy', overwrite: true

    input:
    set val(id), file(aln) from faCh

    output:
      file("${id}_F2G.gap") into fa2gapOut

   when:
      params.fa2gap

    script:
    """
    ${baseDir}/bin/gap ${aln} ${params.fa2gap}
    mv resultF2G.gap ${id}_F2G.gap
    """
}
process gap2Fasta {
    tag "${id}"
    publishDir "${params.output}/fa", mode: 'copy', overwrite: true

    input:
    set val(id), file(aln) from gapCh

    output:
      file("${id}_G2F.fa") into ga2fapOut

   when:
      !params.fa2gap

    script:
    """
    ${baseDir}/bin/gap ${aln} ${params.fa2gap}
    mv resultG2F.fa ${id}_G2F.fa
    """
}
